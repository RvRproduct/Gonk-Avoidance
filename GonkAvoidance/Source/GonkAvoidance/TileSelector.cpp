// Made by Roberto Reynoso (RvRproduct)


#include "TileSelector.h"
#include "InputHandler.h"

// Sets default values
ATileSelector::ATileSelector()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileSelector::BeginPlay()
{
	Super::BeginPlay();

	FVector selectorLocation = FVector::Zero();
	selectorLocation = gameManager->playerUnits[unitSelectIndex]->GetActorLocation();
	selectorLocation.Z = 700.0f;
	SetActorLocation(selectorLocation);
	
}

// Called every frame
void ATileSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gameManager->currentTurnHolder == TurnHolder::Player)
	{
		if (gameManager->currentMode == Mode::None)
		{
			gameManager->currentMode = Mode::SelectUnit;
			SelectUnit(Movement::None);
		}
	}
	

}

// Called to bind functionality to input
void ATileSelector::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATileSelector::SelectUnit(Movement moveSelect)
{
	if (gameManager->currentMode == Mode::SelectUnit)
	{
		ModeColorChange();

		FVector selectorLocation = gameManager->playerUnits[unitSelectIndex]->GetActorLocation();
		selectorLocation.Z = 700.0f;

		if (moveSelect == Movement::None)
		{
			gameManager->playerUnits[unitSelectIndex]->GetActorLocation();
			selectorLocation.Z = 700.0f;
			
			SetActorLocation(selectorLocation);
		}
		else if (moveSelect == Movement::Left)
		{
			unitSelectIndex++;

			if (!(unitSelectIndex < gameManager->playerUnits.Num()))
			{
				unitSelectIndex = 0;
			}

			selectorLocation = gameManager->playerUnits[unitSelectIndex]->GetActorLocation();
			selectorLocation.Z = 700.0f;
			SetActorLocation(selectorLocation);
		}
		else if (moveSelect == Movement::Right)
		{
			unitSelectIndex--;

			if ((unitSelectIndex < 0))
			{
				unitSelectIndex = (gameManager->playerUnits.Num() - 1);
			}

			selectorLocation = gameManager->playerUnits[unitSelectIndex]->GetActorLocation();
			selectorLocation.Z = 700.0f;
			SetActorLocation(selectorLocation);
		}
	}	
}

void ATileSelector::ModeColorChange()
{
	if (gameManager->currentMode == Mode::SelectUnit)
	{
		if (currentSelectColor != SelectColor::SelectUnitColor)
		{
			UStaticMeshComponent* Mesh = this->FindComponentByClass<UStaticMeshComponent>();
			if (Mesh)
			{
				Mesh->SetMaterial(0, unitSelectMaterial);
			}

			currentSelectColor = SelectColor::SelectUnitColor;
		}
	}
	else if (gameManager->currentMode == Mode::Move)
	{
		if (currentSelectColor != SelectColor::MoveColor)
		{
			UStaticMeshComponent* Mesh = this->FindComponentByClass<UStaticMeshComponent>();
			if (Mesh)
			{
				Mesh->SetMaterial(0, unitMovementMaterial);
			}

			currentSelectColor = SelectColor::MoveColor;
		}

	}
}

void ATileSelector::SelectionUnit()
{
	gameManager->currentMode = Mode::Move;
	gameManager->currentPlayerUnitControlled = gameManager->playerUnits[unitSelectIndex];
	currentTile = gameManager->playerUnits[unitSelectIndex]->currentTile;

	FVector selectorLocation = FVector::Zero();
	selectorLocation = currentTile->GetActorLocation();
	selectorLocation.Z = 700.0f;
	SetActorLocation(selectorLocation);

	currentUnit = gameManager->playerUnits[unitSelectIndex];
	currentUnit->activeUnit = true;
	ModeColorChange();
}

void ATileSelector::SelectMovement()
{

	if (currentUnit->playerTargetTile == nullptr)
	{
		currentUnit->playerTargetTile = currentTile;

		gameManager->currentMode = Mode::Undo;
	}	
}

void ATileSelector::UndoMovement()
{
	if (currentUnit->goalPathTile.Key == currentUnit->currentTile)
	{
		currentUnit->undoActive = true;
	}
	
}

void ATileSelector::RedoMovement()
{
	if (currentUnit->goalPathTile.Key == currentUnit->currentTile)
	{
		currentUnit->redoActive = true;
	}
	
}

void ATileSelector::UndoConfirm()
{
	if (currentUnit->goalPathTile.Key == currentUnit->currentTile)
	{
		gameManager->currentMode = Mode::SelectUnit;
		currentUnit->redoActive = false;
		currentUnit->undoActive = false;
		currentUnit->activeUnit = false;
		SelectUnit(Movement::None);
		currentUnit->setPathToTileTarget.Empty();
	}
}


void ATileSelector::ConfirmMovement()
{
	if (currentUnit->goalPathTile.Key == currentUnit->currentTile)
	{
		currentUnit->activeUnit = false;
		gameManager->currentTurnHolder = TurnHolder::Opponent;
		gameManager->OnAIOpponentStart();
		currentUnit->playerTargetTile = nullptr;
		gameManager->currentMode = Mode::None;

		if (gameManager->playerUnits.Num() > 0)
		{
			for (auto* unit : gameManager->playerUnits)
			{
				if (unit != nullptr)
				{
					unit->moveState = true;
				}
			}
		}
	}
}

void ATileSelector::UnitMovement(Movement movementInput)
{
	if (movementInput == Movement::Left)
	{
		if (currentTile->leftTile != nullptr)
		{
			currentTile = currentTile->leftTile;

			FVector selectorLocation = FVector::Zero();
			selectorLocation = currentTile->GetActorLocation();
			selectorLocation.Z = 700.0f;
			SetActorLocation(selectorLocation);
		}
	}
	else if (movementInput == Movement::Right)
	{
		if (currentTile->rightTile != nullptr)
		{
			currentTile = currentTile->rightTile;

			FVector selectorLocation = FVector::Zero();
			selectorLocation = currentTile->GetActorLocation();
			selectorLocation.Z = 700.0f;
			SetActorLocation(selectorLocation);
		}
	}
	else if (movementInput == Movement::Up)
	{
		if (currentTile->upTile != nullptr)
		{
			currentTile = currentTile->upTile;

			FVector selectorLocation = FVector::Zero();
			selectorLocation = currentTile->GetActorLocation();
			selectorLocation.Z = 700.0f;
			SetActorLocation(selectorLocation);
		}
	}
	else if (movementInput == Movement::Down)
	{
		if (currentTile->downTile != nullptr)
		{
			currentTile = currentTile->downTile;

			FVector selectorLocation = FVector::Zero();
			selectorLocation = currentTile->GetActorLocation();
			selectorLocation.Z = 700.0f;
			SetActorLocation(selectorLocation);
		}
	}
	
}

