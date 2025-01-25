// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.h"
#include "BaseTile.h"
#include "WallTile.h"
#include "ColorTile.h"
#include "BaseUnit.h"
#include "MapCreator.generated.h"

UCLASS()
class GONKAVOIDANCE_API AMapCreator : public AActor
{
	GENERATED_BODY()

private:
	FVector mapInitialPosition = GetActorLocation();
	FRotator mapInitialRotation = GetActorRotation();

	int tileHeight = 10;
	int tileWidth = 10;
	
public:	
	// Sets default values for this actor's properties
	AMapCreator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	int lengthPerColumnsAndRows = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	int numberOfColumnsAndRows = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	TArray<TileType> mapTileTypeColumnsAndRows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	TArray<UnitType> mapUnitTypeColumnsAndRows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create Map")
	int unitRaise = 5;

	UPROPERTY(VisibleAnywhere, Category = "The Map")
	TArray<ABaseTile*> mapTiles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateMap(UWorld* World);

	void SetUpTilePathsAndUnits(UWorld* World);
	void SetUnitOnTile(UWorld* World, UnitType unitType, TileType tileType, FVector position, FRotator rotation);

	CurrentTileColor SetInitialUnitTileColor(TileType tileType);

};
