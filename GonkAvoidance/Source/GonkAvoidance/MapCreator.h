// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTile.h"
#include "WallTile.h"
#include "BaseUnit.h"
#include "MapCreator.generated.h"

UCLASS()
class GONKAVOIDANCE_API AMapCreator : public AActor
{
	GENERATED_BODY()

private:
	int tileHeight = 10;
	int tileWidth = 10;
	int numberOfRows = 0;
	int numberOfColumns = 0;
	
public:	
	// Sets default values for this actor's properties
	AMapCreator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	int lengthPerRow = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	int lengthPerColumn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	TArray<TileType> mapTileTypeRows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	TArray<UnitType> mapUnitTypeRows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	TArray<TileType> mapTileTypeColumns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	TArray<UnitType> mapUnitTypeColumns;

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
