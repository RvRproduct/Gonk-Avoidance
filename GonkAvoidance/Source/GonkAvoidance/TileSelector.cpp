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
		if (currentSelectColor != SelectColor::SelectUnitColor)
		{
			UStaticMeshComponent* Mesh = this->FindComponentByClass<UStaticMeshComponent>();
			if (Mesh)
			{
				Mesh->SetMaterial(0, unitSelectMaterial);
			}

			currentSelectColor = SelectColor::SelectUnitColor;
		}

		FVector selectorLocation = FVector::Zero();

		if (moveSelect == Movement::Right)
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
		else if (moveSelect == Movement::Left)
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

void ATileSelector::UnitMovement()
{
	if (gameManager->currentMode == Mode::Move)
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

