// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseUnit.generated.h"

UENUM(BlueprintType)
enum class Combat : uint8
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
enum class CurrentTileColor : uint8
{
	None,
	Red,
	Green,
	Blue
};

UENUM(BlueprintType)
enum class UnitColor : uint8
{
	None,
	Red,
	Green,
	Blue
};

UENUM(BlueprintType)
enum class UnitController : uint8
{
	None,
	AI,
	Player,
	PlayerTwo
};

UCLASS()
class GONKAVOIDANCE_API ABaseUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseUnit();

	// Unit Controller By (AI, Player, PlayerTwo)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Controller Type")
	UnitController unitController = UnitController::None;

	// Unit Color and Current Tile Color
	CurrentTileColor currentColorTile = CurrentTileColor::None;
	UnitColor unitColor = UnitColor::None;

	// Combat Choice
	Combat combatChoice = Combat::None;

	// Stats
	int tileMovementRange = 6;
	int health = 100;
	int attackPower = 10;
	int defensePower = 5;
	float evasionRate = 30.0f;

	int combatPowerBoost = 2;	
	float hitRateBoost = 25.0f;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
