// Made by Roberto Reynoso (RvRproduct)


#include "GameManager.h"

// Initialize the static instance to nullptr
AGameManager* AGameManager::Instance = nullptr;

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

	if (Instance == nullptr)
	{
		Instance = this;
	}
	else
	{
		Destroy();
	}
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AGameManager* AGameManager::GetInstance(UWorld* World)
{
	if (Instance == nullptr)
	{
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			Instance = World->SpawnActor<AGameManager>(AGameManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		}
	}

	return Instance;
}

