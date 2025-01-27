// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"


UENUM(BlueprintType)
enum class TurnHolder : uint8
{
	None,
	Player,
	Opponent
};

UENUM(BlueprintType)
enum class Mode : uint8
{
	None,
	SelectUnit,
	Move,
	Combat
};

class ABaseUnit;
class ABaseTile;

UCLASS()
class GONKAVOIDANCE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	Mode currentMode = Mode::SelectUnit;
	int turnNumber = 1;

	TurnHolder currentTurnHolder = TurnHolder::Player;

	TArray<ABaseUnit*> playerUnits;
	ABaseUnit* currentPlayerUnitControlled;
	ABaseTile* currentSelectorTile;

	TArray<ABaseUnit*> opponentUnits;

	bool mapCreationFinished = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnAIOpponentStart();
	void CheckCurrentTurnHolder();
	void ChangeMode(Mode modeChange);

};
