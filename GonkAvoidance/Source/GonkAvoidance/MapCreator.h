// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTile.h"
#include "WallTile.h"
#include "BaseUnit.h"
#include "MapCreator.generated.h"

UENUM(BlueprintType)
enum class TileTypes : uint8
{
	None,
	Wall,
	Red,
	Green,
	Blue
};

UCLASS()
class GONKAVOIDANCE_API AMapCreator : public AActor
{
	GENERATED_BODY()

private:
	int tileHeight = 10;
	int tileWidth = 10;
	
public:	
	// Sets default values for this actor's properties
	AMapCreator();

	TArray<TArray<ABaseTile*>> mapTiles;
	TArray<ABaseUnit*> playerUnits;
	TArray<ABaseUnit*> opponentUnits;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
