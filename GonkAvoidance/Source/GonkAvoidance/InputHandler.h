// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileSelector.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputHandler.generated.h"

UENUM(BlueprintType)
enum class CombatSelection : uint8
{
	None,
	Attack,
	Strike,
	Charge,
	Defend,
	Counter,
	Evade
};

UENUM(BlueprintType)
enum class GeneralSelection : uint8
{
	None,
	ConfirmMovement,
	UndoMovement,
	RedoMovement,
	ConfirmCombat
};

UENUM(BlueprintType)
enum class Movement : uint8
{
	None,
	Left,
	Right,
	Up,
	Down
};

class Command;

UCLASS()
class GONKAVOIDANCE_API AInputHandler : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInputHandler();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile Selector")
	ATileSelector* tileSelector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Manager")
	AGameManager* gameManager;


	UnitType unitType = UnitType::None;


	Command
		*upArrow,
		*downArrow,
		*leftArrow,
		*rightArrow,
		*keySpace;

	void GeneralSelect(GeneralSelection generalSelection);
	void CombatSelect(CombatSelection combatSelection);
	void MoveSelect(Movement moveInput);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Mapping")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SelectAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Select(const FInputActionValue& Value);

};
