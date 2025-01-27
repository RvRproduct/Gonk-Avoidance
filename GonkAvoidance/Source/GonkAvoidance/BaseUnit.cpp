// Made by Roberto Reynoso (RvRproduct)


#include "BaseUnit.h"
#include "Kismet/GameplayStatics.h"
#include "Algo/Reverse.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gameManager == nullptr || !gameManager->mapCreationFinished) { return; }

	if (gameManager->mapCreationFinished && !unitSetup)
	{
		playerUnits = gameManager->playerUnits;
		opponentUnits = gameManager->opponentUnits;


		lastPathTile.Key = currentTile;

		if (currentTile != nullptr)
		{
			if (nextTile == nullptr)
			{
				nextTile = currentTile;
			}

			this->SetActorLocation(currentTile->GetActorLocation());
		}

		unitSetup = true;
	}

	if (!unitSetup) { return; }

	if (unitController == UnitController::AI && activeUnit)
	{
		if (gameManager->currentTurnHolder != TurnHolder::Opponent) { return; }

		if (hasReachedDestination)
		{
			if (!hasStartedSearch)
			{
				hasStartedSearch = true;
				BeginSearchTilePath();
			}

			if (!tilePathDone)
			{
				SearchTilePath(lastPathTile);
			}

			if (tilePathDone)
			{
				SetTilePath();
				hasReachedDestination = false;
			}
		}
		else
		{
			if (currentTile != goalPathTile.Key)
			{
				Seek(nextTile->GetActorLocation(), DeltaTime);
			}

			if (currentTile == goalPathTile.Key)
			{
				gameManager->currentTurnHolder = TurnHolder::Player;
				activeUnit = false;
				hasSelectedMovement = false;
				hasStartedSearch = false;
				hasReachedDestination = true;
			}
		}
	}
	
	if (unitController == UnitController::Player)
	{
		if (gameManager->currentTurnHolder != TurnHolder::Player) { return; }

		if (hasReachedDestination && gameManager->currentMode != Mode::SelectUnit && gameManager->currentMode != Mode::Move && activeUnit)
		{

			if (!undoActive && !redoActive && moveState)
			{
				if (!hasStartedSearch)
				{
					hasStartedSearch = true;
					BeginSearchTilePath();
				}

				if (!tilePathDone)
				{
					SearchTilePath(lastPathTile);
				}

				if (tilePathDone)
				{
					SetTilePath();
					hasReachedDestination = false;
				}
			}
			else if (gameManager->currentMode == Mode::Undo && undoActive)
			{
				undoActive = false;
				gameManager->currentMode = Mode::Redo;
				setPathToTileTarget = undoPath;
				// Set the new goal
				if (setPathToTileTarget.Num() > 0)
				{
					goalPathTile.Key = setPathToTileTarget[0];
				}

				hasReachedDestination = false;
			}
			else if (gameManager->currentMode == Mode::Redo && redoActive)
			{
				redoActive = false;
				gameManager->currentMode = Mode::Undo;
				setPathToTileTarget = redoPath;

				// Set the new goal
				if (setPathToTileTarget.Num() > 0)
				{
					goalPathTile.Key = setPathToTileTarget[0];
				}

				hasReachedDestination = false;
			}
		}
		else
		{
			if (currentTile != goalPathTile.Key)
			{
				Seek(nextTile->GetActorLocation(), DeltaTime);
			}

			if (currentTile == goalPathTile.Key)
			{

				hasSelectedMovement = false;
				hasStartedSearch = false;
				hasReachedDestination = true;
			}
		}
	}
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseUnit::ClearTilePath()
{
	setPathToTileTarget.Empty();

	startPathTile.Key = nullptr;

	if (!startPathTile.Value)
	{
		startPathTile.Value = new TilePathFinding();
	}

	startPathTile.Value->F = 0.0f;
	startPathTile.Value->G = 0.0f;
	startPathTile.Value->H = 0.0f;
	startPathTile.Value->parentTile = nullptr;
	startPathTile.Value->parentTileFinding = nullptr;

	if (!goalPathTile.Value)
	{
		goalPathTile.Value = new TilePathFinding();
	}

	//goalPathTile.Key = nullptr;
	goalPathTile.Value->F = 0.0f;
	goalPathTile.Value->G = 0.0f;
	goalPathTile.Value->H = 0.0f;
	goalPathTile.Value->parentTile = nullptr;
	goalPathTile.Value->parentTileFinding = nullptr;

	if (!lastPathTile.Value)
	{
		lastPathTile.Value = new TilePathFinding();
	}

	lastPathTile.Value->F = 0.0f;
	lastPathTile.Value->G = 0.0f;
	lastPathTile.Value->H = 0.0f;
	lastPathTile.Value->parentTile = nullptr;
	lastPathTile.Value->parentTileFinding = nullptr;
}

void ABaseUnit::BeginSearchTilePath()
{
	tilePathDone = false;
	ClearTilePath();

	startPathTile.Key = currentTile;
	

	if (unitController == UnitController::AI)
	{
		ABaseUnit* targetPlayerUnit = nullptr;
		float distFromPlayerUnit = INFINITY;

		for (ABaseUnit* playerUnit : playerUnits)
		{
			float distFromThisPlayerUnit = FVector::Dist(this->GetActorLocation(), playerUnit->GetActorLocation());

			if (distFromThisPlayerUnit < distFromPlayerUnit)
			{
				targetPlayerUnit = playerUnit;
				distFromPlayerUnit = distFromThisPlayerUnit;
			}
		}

		if (targetPlayerUnit != nullptr)
		{
			ABaseTile* targetAttackTile = nullptr;
			float distFromAttackTile = INFINITY;

			// Checking Left Tile From Target

			if (targetPlayerUnit->currentTile == nullptr) { return; }

			if (targetPlayerUnit->currentTile->leftTile != nullptr)
			{
				float distFromThisAttackTile = FVector::Dist(this->GetActorLocation(), targetPlayerUnit->currentTile->leftTile->GetActorLocation());
				
				if (distFromThisAttackTile < distFromAttackTile)
				{
					targetAttackTile = targetPlayerUnit->currentTile->leftTile;
					distFromAttackTile = distFromThisAttackTile;
				}
			}

			// Checking Right Tile From Target
			if (targetPlayerUnit->currentTile->rightTile != nullptr)
			{
				float distFromThisAttackTile = FVector::Dist(this->GetActorLocation(), targetPlayerUnit->currentTile->rightTile->GetActorLocation());

				if (distFromThisAttackTile < distFromAttackTile)
				{
					targetAttackTile = targetPlayerUnit->currentTile->rightTile;
					distFromAttackTile = distFromThisAttackTile;
				}
			}

			// Checking Up Tile From Target
			if (targetPlayerUnit->currentTile->upTile != nullptr)
			{
				float distFromThisAttackTile = FVector::Dist(this->GetActorLocation(), targetPlayerUnit->currentTile->upTile->GetActorLocation());

				if (distFromThisAttackTile < distFromAttackTile)
				{
					targetAttackTile = targetPlayerUnit->currentTile->upTile;
					distFromAttackTile = distFromThisAttackTile;
				}
			}

			// Checking Down Tile From Target
			if (targetPlayerUnit->currentTile->downTile != nullptr)
			{
				float distFromThisAttackTile = FVector::Dist(this->GetActorLocation(), targetPlayerUnit->currentTile->downTile->GetActorLocation());

				if (distFromThisAttackTile < distFromAttackTile)
				{
					targetAttackTile = targetPlayerUnit->currentTile->downTile;
					distFromAttackTile = distFromThisAttackTile;
				}
			}

			if (targetAttackTile != nullptr)
			{
				goalPathTile.Key = targetAttackTile;

				if (currentTile == goalPathTile.Key)
				{
					tilePathDone = true;
					return;
				}
			}	
		}

		openPathToTileTarget.Empty();
		closedPathToTileTarget.Empty();

		openPathToTileTarget.Add(startPathTile);
		lastPathTile.Key = startPathTile.Key;

		
	}
	else if (unitController == UnitController::Player)
	{
		if (playerTargetTile != nullptr)
		{
			goalPathTile.Key = playerTargetTile;

			if (currentTile == goalPathTile.Key)
			{
				return;
			}
		}
		else
		{
			goalPathTile.Key = currentTile;
			return;
		}

		openPathToTileTarget.Empty();
		closedPathToTileTarget.Empty();

		openPathToTileTarget.Add(startPathTile);
		lastPathTile.Key = startPathTile.Key;
	}
}

void ABaseUnit::SearchTilePath(TPair<ABaseTile*, TilePathFinding*> thisPathTile)
{
	if (thisPathTile.Key == nullptr)
	{
		return;
	}

	if (thisPathTile.Key == goalPathTile.Key)
	{
		tilePathDone = true;
		return;
	}

	// Checking Left Neighbor
	if (thisPathTile.Key->leftTile != nullptr)
	{
		if (!IsClosedTile(thisPathTile.Key->leftTile))
		{
			SetTileGHF(thisPathTile, thisPathTile.Key->leftTile, goalPathTile.Key);
		}
	}

	// Checking Right Neighbor
	if (thisPathTile.Key->rightTile != nullptr)
	{
		if (!IsClosedTile(thisPathTile.Key->rightTile))
		{
			SetTileGHF(thisPathTile, thisPathTile.Key->rightTile, goalPathTile.Key);
		}
	}

	// Checking Up Neighbor
	if (thisPathTile.Key->upTile != nullptr)
	{
		if (!IsClosedTile(thisPathTile.Key->upTile))
		{
			SetTileGHF(thisPathTile, thisPathTile.Key->upTile, goalPathTile.Key);
		}
	}

	// Checking Down Neighbor
	if (thisPathTile.Key->downTile != nullptr)
	{
		if (!IsClosedTile(thisPathTile.Key->downTile))
		{
			SetTileGHF(thisPathTile, thisPathTile.Key->downTile, goalPathTile.Key);
		}
	}

	// By F First
	openPathToTileTarget.Sort([](const TPair<ABaseTile*, TilePathFinding*> tilePathA, const TPair<ABaseTile*, TilePathFinding*> tilePathB)
		{
			return tilePathA.Value->F < tilePathB.Value->F;
		});

	// The H Second
	openPathToTileTarget.Sort([](const TPair<ABaseTile*, TilePathFinding*> tilePathA, const TPair<ABaseTile*, TilePathFinding*> tilePathB)
		{
			return tilePathA.Value->H < tilePathB.Value->H;
		});

	if (!(openPathToTileTarget.Num() > 0))
	{
		return;
	}

	TPair<ABaseTile*, TilePathFinding*> markerPathTile = openPathToTileTarget[0];
	closedPathToTileTarget.Add(markerPathTile);

	openPathToTileTarget.RemoveAt(0);

	lastPathTile = markerPathTile;
}

void ABaseUnit::SetTileGHF(TPair<ABaseTile*, TilePathFinding*> thisPathTile, ABaseTile* neighborTile, ABaseTile* goalTile)
{
	if (!thisPathTile.Key || !neighborTile || !goalTile)
	{
		return;
	}

	float G = FVector::Dist(thisPathTile.Key->GetActorLocation(), neighborTile->GetActorLocation()) + thisPathTile.Value->G;
	float H = FVector::Dist(neighborTile->GetActorLocation(), goalTile->GetActorLocation());
	float F = G + H;

	if (!UpdateTile(neighborTile, G, H, F, thisPathTile))
	{
		TPair<ABaseTile*, TilePathFinding*> newNeighborTile;
		newNeighborTile.Value = new TilePathFinding();
		newNeighborTile.Key = neighborTile;
		newNeighborTile.Value->G = G;
		newNeighborTile.Value->H = H;
		newNeighborTile.Value->F = F;
		newNeighborTile.Value->parentTile = thisPathTile.Key;
		newNeighborTile.Value->parentTileFinding = thisPathTile.Value;

		openPathToTileTarget.Add(newNeighborTile);
	}
}

bool ABaseUnit::UpdateTile(ABaseTile* neighborTile, float G, float H, float F, TPair<ABaseTile*, TilePathFinding*> parentPathTile)
{
	for (TPair<ABaseTile*, TilePathFinding*> openTile : openPathToTileTarget)
	{
		if (openTile.Key == neighborTile)
		{
			openTile.Value->G = G;
			openTile.Value->H = H;
			openTile.Value->F = F;
			openTile.Value->parentTile = parentPathTile.Key;
			openTile.Value->parentTileFinding = parentPathTile.Value;
			return true;
		}
	}

	return false;
}

bool ABaseUnit::IsClosedTile(ABaseTile* thisTile)
{
	for (const TPair<ABaseTile*, TilePathFinding*>& closedTile : closedPathToTileTarget)
	{
		if (closedTile.Key == thisTile)
		{
			return true;
		}
	}

	return false;
}

void ABaseUnit::SetTilePath()
{
	if (!lastPathTile.Key || !lastPathTile.Value)
	{
		return;
	}

	ABaseTile* beginPathTile = lastPathTile.Key;
	TilePathFinding* beginPathTileFinding = lastPathTile.Value;

	setPathToTileTarget.Add(beginPathTile);

	while (startPathTile.Key != beginPathTile && beginPathTile != nullptr)
	{
		beginPathTile = beginPathTileFinding->parentTile;
		setPathToTileTarget.Add(beginPathTile);
		beginPathTileFinding = beginPathTileFinding->parentTileFinding;
	}

	if (gameManager->currentTurnHolder == TurnHolder::Player && unitController == UnitController::Player)
	{
		if (setPathToTileTarget.Num() > 1)
		{

			undoPath = setPathToTileTarget;
			Algo::Reverse(undoPath);
			redoPath = setPathToTileTarget;

			moveState = false;
		}
	}
	

	if (beginPathTile != startPathTile.Key)
	{
		setPathToTileTarget.Add(startPathTile.Key);
	}

	if (gameManager->currentTurnHolder == TurnHolder::Opponent && unitController == UnitController::AI)
	{
		if (setPathToTileTarget.Num() > 0)
		{
			while (nextTile == currentTile && setPathToTileTarget.Num() > 0)
			{
				nextTile = setPathToTileTarget.Pop();
			}
		}
	}
	
}

void ABaseUnit::Seek(FVector tilePosition, float DeltaTime)
{
	float distanceToTile = FVector::Dist(this->GetActorLocation(), tilePosition);
	float ArrivalRadius = 3.0f;

	FVector newUnitPosition = tilePosition;
	newUnitPosition.Z = this->GetActorLocation().Z;

	if (distanceToTile <= ArrivalRadius)
	{
		currentVelocity = FVector::ZeroVector;
		SetActorLocation(newUnitPosition);
		
		currentTile = nextTile;

		if (!hasReachedDestination)
		{
			if (setPathToTileTarget.Num() > 0)
			{
				nextTile = setPathToTileTarget.Pop();
			}
		}
		

		return;
	}

	FVector direction = (newUnitPosition - this->GetActorLocation()).GetSafeNormal();
	currentVelocity = direction * maxSpeed;

	SetActorLocation(this->GetActorLocation() + currentVelocity * DeltaTime);
}