// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameManager.h"
#include "BaseTile.h"
#include "BaseUnit.h"
#include "TileSelector.generated.h"

UENUM(BlueprintType)
enum class SelectColor : uint8
{
	None,
	SelectUnitColor,
	MoveColor,
	CombatColor
};

enum class Movement : uint8;

UCLASS()
class GONKAVOIDANCE_API ATileSelector : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATileSelector();

	SelectColor currentSelectColor = SelectColor::None;

	ABaseTile* currentTile;
	ABaseUnit* currentUnit;
	int unitSelectIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Manager")
	AGameManager* gameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* unitSelectMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* unitMovementMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SelectUnit(Movement moveSelect);
	void ModeColorChange();
	void SelectionUnit();
	void UnitMovement(Movement movementInput);
	void SelectMovement();

};
