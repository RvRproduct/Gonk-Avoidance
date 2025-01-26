// Made by Roberto Reynoso (RvRproduct)


#include "BaseUnit.h"

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

	lastPathTile.Key = currentTile;

	if (currentTile != nullptr)
	{
		if (nextTile == nullptr)
		{
			nextTile = currentTile;
		}

		this->SetActorLocation(currentTile->GetActorLocation());
	}
	
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (hasReachedDestination && hasSelectedMovement)
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
			hasSelectedMovement = false;
			hasStartedSearch = false;
			hasReachedDestination = true;
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

	goalPathTile.Key = nullptr;
	goalPathTile.Value->F = 0.0f;
	goalPathTile.Value->G = 0.0f;
	goalPathTile.Value->H = 0.0f;
	goalPathTile.Value->parentTile = nullptr;
	goalPathTile.Value->parentTileFinding = nullptr;

	if (!lastPathTile.Value)
	{
		lastPathTile.Value = new TilePathFinding();
	}

	lastPathTile.Key = nullptr;
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

	if (this)
}

bool ABaseUnit::UpdateTile(ABaseTile* neighborTile, float G, float H, float F, TPair<ABaseTile*, TilePathFinding*> parentPathTile)
{
	return false;
}

void ABaseUnit::SetTileGHF(TPair<ABaseTile*, TilePathFinding*> thisPathTile, ABaseTile* neighborTile, ABaseTile* goalTile)
{

}

bool ABaseUnit::IsClosedTile(ABaseTile* thisTile)
{
	return false;
}

ABaseTile* ABaseUnit::GetClosestPossibleTileToPlayer()
{
	return nullptr;
}

void ABaseUnit::SetTilePath()
{

}

void ABaseUnit::Seek(FVector tilePosition, float DeltaTime)
{

}
