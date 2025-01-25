// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UENUM(BlueprintType)
enum class CurrentMode : uint8
{
	None,
	Move,
	Combat
};

class ABaseUnit;


UCLASS()
class GONKAVOIDANCE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	

	static AGameManager* GetInstance(UWorld* World);

	// Sets default values for this actor's properties
	AGameManager();

	CurrentMode currentMode = CurrentMode::Move;
	int turnNumber = 1;

	TArray<ABaseUnit*> playerUnits;
	TArray<ABaseUnit*> opponentUnits;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	static AGameManager* Instance;

};
