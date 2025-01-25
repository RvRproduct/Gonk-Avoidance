// Made by Roberto Reynoso (RvRproduct)


#include "MapCreator.h"

// Sets default values
AMapCreator::AMapCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapCreator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapCreator::CreateMap(UWorld* World)
{
	if (!World) { return; }

	FVector SpawnLocation(mapInitialPosition);
	FRotator SpawnRotation(mapInitialRotation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int currentColumn = 1; currentColumn <= numberOfColumnsAndRows; currentColumn++)
	{
		for (int currentRow = 0; currentRow < lengthPerColumnsAndRows; currentRow++)
		{
			if (mapTileTypeColumnsAndRows[currentRow * currentColumn] == TileType::Wall)
			{
				AWallTile* SpawnedTile = World->SpawnActor<AWallTile>(AWallTile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Wall;
				SpawnedTile->validTile = false;
				mapTiles.Add(SpawnedTile);
			}
			else if (mapTileTypeColumnsAndRows[currentRow * currentColumn] == TileType::Red)
			{
				AColorTile* SpawnedTile = World->SpawnActor<AColorTile>(AColorTile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Red;
				SpawnedTile->validTile = true;
				mapTiles.Add(SpawnedTile);
			}
			else if (mapTileTypeColumnsAndRows[currentRow * currentColumn] == TileType::Green)
			{
				AColorTile* SpawnedTile = World->SpawnActor<AColorTile>(AColorTile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Green;
				SpawnedTile->validTile = true;
				mapTiles.Add(SpawnedTile);
			}
			else if (mapTileTypeColumnsAndRows[currentRow * currentColumn] == TileType::Blue)
			{
				AColorTile* SpawnedTile = World->SpawnActor<AColorTile>(AColorTile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Blue;
				SpawnedTile->validTile = true;
				mapTiles.Add(SpawnedTile);
			}

			SpawnLocation.X += tileWidth;
		}

		SpawnLocation.X = mapInitialPosition.X;
		SpawnLocation.Y += tileHeight;
	}
}


void AMapCreator::SetUpTilePathsAndUnits(UWorld* World)
{
	for (int currentColumn = 1; currentColumn <= numberOfColumnsAndRows; currentColumn++)
	{
		for (int currentRow = 0; currentRow < lengthPerColumnsAndRows; currentRow++)
		{

		}
	}
}

void AMapCreator::SetUnitOnTile(UWorld* World, UnitType unitType, TileType tileType, FVector position, FRotator rotation)
{
	FVector SpawnLocation = position;
	FRotator SpawnRotation = rotation;

	SpawnLocation.Z += unitRaise;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (unitType == UnitType::None)
	{
		return;
	}
	else if (unitType == UnitType::RedPlayer)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(ABaseUnit::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Red;
		SpawnedUnit->unitController = UnitController::Player;
	}
	else if (unitType == UnitType::GreenPlayer)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(ABaseUnit::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Green;
		SpawnedUnit->unitController = UnitController::Player;
	}
	else if (unitType == UnitType::BluePlayer)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(ABaseUnit::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Blue;
		SpawnedUnit->unitController = UnitController::Player;
	}
	else if (unitType == UnitType::RedPlayer)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(ABaseUnit::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Red;
		SpawnedUnit->unitController = UnitController::Player;
	}
	else if (unitType == UnitType::RedPlayer)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(ABaseUnit::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Red;
		SpawnedUnit->unitController = UnitController::Player;
	}
}

CurrentTileColor AMapCreator::SetInitialUnitTileColor(TileType tileType)
{
	if (tileType == TileType::Red)
	{
		return CurrentTileColor::Red;
	}
	else if (tileType == TileType::Green)
	{
		return CurrentTileColor::Green;
	}
	else if (tileType == TileType::Blue)
	{
		return CurrentTileColor::Blue;
	}

	return CurrentTileColor::None;
}
