// Made by Roberto Reynoso (RvRproduct)


#include "InputHandler.h"
#include "Command.h"

// Sets default values
AInputHandler::AInputHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	upArrow = nullptr;
	downArrow = nullptr;
	leftArrow = nullptr;
	rightArrow = nullptr;
	zKey = nullptr;
	yKey = nullptr;
	keySpace = nullptr;

}

// Called when the game starts or when spawned
void AInputHandler::BeginPlay()
{
	Super::BeginPlay();

	upArrow = new MoveUpCommand();
	upArrow->tileSelector = tileSelector;
	upArrow->gameManager = gameManager;

	downArrow = new MoveDownCommand();
	downArrow->tileSelector = tileSelector;
	downArrow->gameManager = gameManager;

	leftArrow = new MoveLeftCommand();
	leftArrow->tileSelector = tileSelector;
	leftArrow->gameManager = gameManager;

	rightArrow = new MoveRightCommand();
	rightArrow->tileSelector = tileSelector;
	rightArrow->gameManager = gameManager;

	zKey = new UndoCommand();
	zKey->tileSelector = tileSelector;
	zKey->gameManager = gameManager;

	yKey = new RedoCommand();
	yKey->tileSelector = tileSelector;
	yKey->gameManager = gameManager;

	keySpace = new SelectCommand();
	keySpace->tileSelector = tileSelector;
	keySpace->gameManager = gameManager;
	
}

// Called every frame
void AInputHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInputHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Binding Each Input
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInputHandler::Move);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &AInputHandler::Select);
		EnhancedInputComponent->BindAction(UndoAction, ETriggerEvent::Triggered, this, &AInputHandler::Undo);
		EnhancedInputComponent->BindAction(RedoAction, ETriggerEvent::Triggered, this, &AInputHandler::Redo);
	}

}

void AInputHandler::Move(const FInputActionValue& Value)
{
	FVector2D movementInput = Value.Get<FVector2D>();

	if (movementInput.X < 0) // Left
	{
		MoveSelect(Movement::Left);
	}
	else if (movementInput.X > 0) // Right
	{

		MoveSelect(Movement::Right);
	}
	else if (movementInput.Y > 0) // Up
	{
		MoveSelect(Movement::Up);
	}
	else if (movementInput.Y < 0) // Down
	{
		MoveSelect(Movement::Down);
	}
}

void AInputHandler::Select(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		keySpace->Execute();
	}
}


void AInputHandler::MoveSelect(Movement moveInput)
{
	if (moveInput == Movement::Left)
	{
		leftArrow->Execute();
	}
	else if (moveInput == Movement::Right)
	{
		rightArrow->Execute();
	}
	else if (moveInput == Movement::Up)
	{
		upArrow->Execute();
	}
	else if (moveInput == Movement::Down)
	{
		downArrow->Execute();
	}
}

void AInputHandler::Undo(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		zKey->Execute();
	}
	
}

void AInputHandler::Redo(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		yKey->Execute();
	}
}

void AInputHandler::GeneralSelect(GeneralSelection generalSelection)
{
	if (generalSelection == GeneralSelection::ConfirmMovement)
	{

	}
	else if (generalSelection == GeneralSelection::ConfirmUnit)
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

