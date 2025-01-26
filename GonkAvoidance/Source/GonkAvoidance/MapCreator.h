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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create Map")
	TSubclassOf<AWallTile> wallTileBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create Map")
	TSubclassOf<AColorTile> colorTileBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create Map")
	TSubclassOf<ABaseUnit> unitBlueprint;

	UPROPERTY(VisibleAnywhere, Category = "The Map")
	TArray<ABaseTile*> mapTiles;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Manager")
	AGameManager* gameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* redMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* blueMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateMap(UWorld* World);

	void SetUpTilePathsAndUnits(UWorld* World);
	void SetUnitOnTile(UWorld* World, UnitType unitType, TileType tileType, FVector position, FRotator rotation, int currentTileIndex);

	CurrentTileColor SetInitialUnitTileColor(TileType tileType);

};
