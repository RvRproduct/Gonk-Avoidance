// Made by Roberto Reynoso (RvRproduct)


#include "InputHandler.h"

// Sets default values
AInputHandler::AInputHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	upArrow = nullptr;
	downArrow = nullptr;
	leftArrow = nullptr;
	rightArrow = nullptr;
	keyEnter = nullptr;

}

// Called when the game starts or when spawned
void AInputHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInputHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

