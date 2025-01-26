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
	keySpace = nullptr;

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

void AInputHandler::MoveSelect(Movement moveInput)
{
	if (moveInput == Movement::Left)
	{

	}
	else if (moveInput == Movement::Right)
	{

	}
	else if (moveInput == Movement::Up)
	{

	}
	else if (moveInput == Movement::Down)
	{

	}
}

void AInputHandler::GeneralSelect(GeneralSelection generalSelection)
{
	if (generalSelection == GeneralSelection::ConfirmMovement)
	{

	}
	else if (generalSelection == GeneralSelection::UndoMovement)
	{

	}
	else if (generalSelection == GeneralSelection::RedoMovement)
	{

	}
	else if (generalSelection == GeneralSelection::ConfirmCombat)
	{

	}
}

void AInputHandler::CombatSelect(CombatSelection combatSelection)
{
	if (combatSelection == CombatSelection::Attack)
	{

	}
	else if (combatSelection == CombatSelection::Strike)
	{

	}
	else if (combatSelection == CombatSelection::Charge)
	{

	}
	else if (combatSelection == CombatSelection::Defend)
	{

	}
	else if (combatSelection == CombatSelection::Counter)
	{

	}
	else if (combatSelection == CombatSelection::Evade)
	{

	}
}

