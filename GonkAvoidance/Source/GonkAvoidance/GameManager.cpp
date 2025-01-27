// Made by Roberto Reynoso (RvRproduct)
#include "GameManager.h"

#include "BaseUnit.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::CheckCurrentTurnHolder()
{
	if (turnNumber % 2 != 0)
	{
		currentTurnHolder = TurnHolder::Player;
	}
	else
	{
		currentTurnHolder = TurnHolder::Opponent;
	}
}

void AGameManager::OnAIOpponentStart()
{
	if (opponentUnits.Num() > 0)
	{
		int randomUnitSelect = FMath::RandRange(0, opponentUnits.Num() - 1);

		for (int unitIndex = 0; unitIndex < opponentUnits.Num(); unitIndex)
		{
			if (unitIndex == randomUnitSelect)
			{
				opponentUnits[unitIndex]->activeUnit = true;
			}
			else
			{
				opponentUnits[unitIndex]->activeUnit = false;
			}
		}
	}

	
}

void AGameManager::ChangeMode(Mode modeChange)
{
	currentMode = modeChange;
}

