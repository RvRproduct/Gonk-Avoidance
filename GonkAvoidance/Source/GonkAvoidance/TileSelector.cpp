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

		FVector selectorLocation = FVector::Zero();

		if (moveSelect == Movement::Left)
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
	ModeColorChange();
}

void ATileSelector::SelectMovement()
{

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

