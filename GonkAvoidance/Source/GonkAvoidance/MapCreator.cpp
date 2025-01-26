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

	UWorld* World = GetWorld();

	CreateMap(World);
}

// Called every frame
void AMapCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapCreator::CreateMap(UWorld* World)
{
	if (!World) { return; }

	if (!wallTileBlueprint || !colorTileBlueprint) { return; }

	FVector SpawnLocation(mapInitialPosition);
	FRotator SpawnRotation(mapInitialRotation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	int currentTileIndex = 0;
	for (int currentColumn = 0; currentColumn < numberOfColumnsAndRows; currentColumn++)
	{
		for (int currentRow = 0; currentRow < lengthPerColumnsAndRows; currentRow++)
		{
			if (mapTileTypeColumnsAndRows[currentTileIndex] == TileType::Wall)
			{
				AWallTile* SpawnedTile = World->SpawnActor<AWallTile>(wallTileBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Wall;
				SpawnedTile->validTile = false;
				mapTiles.Add(SpawnedTile);
			}
			else if (mapTileTypeColumnsAndRows[currentTileIndex] == TileType::Red)
			{
				AColorTile* SpawnedTile = World->SpawnActor<AColorTile>(colorTileBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Red;
				SpawnedTile->validTile = true;
				mapTiles.Add(SpawnedTile);
			}
			else if (mapTileTypeColumnsAndRows[currentTileIndex] == TileType::Green)
			{
				AColorTile* SpawnedTile = World->SpawnActor<AColorTile>(colorTileBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Green;
				SpawnedTile->validTile = true;
				mapTiles.Add(SpawnedTile);
			}
			else if (mapTileTypeColumnsAndRows[currentTileIndex] == TileType::Blue)
			{
				AColorTile* SpawnedTile = World->SpawnActor<AColorTile>(colorTileBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
				SpawnedTile->tileType = TileType::Blue;
				SpawnedTile->validTile = true;
				mapTiles.Add(SpawnedTile);
			}

			SpawnLocation.X += tileWidth * 100;
			currentTileIndex++;
		}

		SpawnLocation.X = mapInitialPosition.X;
		SpawnLocation.Y += tileHeight * 100;
	}

	SetUpTilePathsAndUnits(World);
}


void AMapCreator::SetUpTilePathsAndUnits(UWorld* World)
{
	int currentTileIndex = 0;
	for (int currentColumn = 0; currentColumn < numberOfColumnsAndRows; currentColumn++)
	{
		for (int currentRow = 0; currentRow < lengthPerColumnsAndRows; currentRow++)
		{
			// Left
			if (currentTileIndex - 1 >= currentColumn * lengthPerColumnsAndRows)
			{
				if (currentTileIndex - 1 >= 0)
				{
					if (mapTiles[currentTileIndex - 1]->validTile)
					{
						mapTiles[currentTileIndex]->leftTile = mapTiles[currentTileIndex - 1];

						SetUnitOnTile(World, 
							mapUnitTypeColumnsAndRows[currentTileIndex],
							mapTileTypeColumnsAndRows[currentTileIndex],
							mapTiles[currentTileIndex]->GetActorLocation(),
							mapTiles[currentTileIndex]->GetActorRotation());
					}
				}
			}

			// Right
			if (currentTileIndex + 1 < (currentColumn + 1) * lengthPerColumnsAndRows)
			{
				if (currentTileIndex + 1 < mapTiles.Num())
				{
					if (mapTiles[currentTileIndex + 1]->validTile)
					{
						mapTiles[currentTileIndex]->rightTile = mapTiles[currentTileIndex + 1];

						SetUnitOnTile(World,
							mapUnitTypeColumnsAndRows[currentTileIndex],
							mapTileTypeColumnsAndRows[currentTileIndex],
							mapTiles[currentTileIndex]->GetActorLocation(),
							mapTiles[currentTileIndex]->GetActorRotation());
					}
				}
			}

			// Up
			if (currentTileIndex - lengthPerColumnsAndRows >= 0)
			{
				if (mapTiles[currentTileIndex - lengthPerColumnsAndRows]->validTile)
				{
					mapTiles[currentTileIndex]->upTile = mapTiles[currentTileIndex - lengthPerColumnsAndRows];

					SetUnitOnTile(World,
						mapUnitTypeColumnsAndRows[currentTileIndex],
						mapTileTypeColumnsAndRows[currentTileIndex],
						mapTiles[currentTileIndex]->GetActorLocation(),
						mapTiles[currentTileIndex]->GetActorRotation());
				}
			}

			// Down
			if (currentTileIndex + lengthPerColumnsAndRows < mapTiles.Num())
			{
				if (mapTiles[currentTileIndex + lengthPerColumnsAndRows]->validTile)
				{
					mapTiles[currentTileIndex]->downTile = mapTiles[currentTileIndex + lengthPerColumnsAndRows];

					SetUnitOnTile(World,
						mapUnitTypeColumnsAndRows[currentTileIndex],
						mapTileTypeColumnsAndRows[currentTileIndex],
						mapTiles[currentTileIndex]->GetActorLocation(),
						mapTiles[currentTileIndex]->GetActorRotation());
				}
			}

			currentTileIndex++;	
		}
	}
}

void AMapCreator::SetUnitOnTile(UWorld* World, UnitType unitType, TileType tileType, FVector position, FRotator rotation)
{
	if (tileType == TileType::Wall) { return; }

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
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(unitBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Red;
		SpawnedUnit->unitController = UnitController::Player;
	}
	else if (unitType == UnitType::GreenPlayer)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(unitBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Green;
		SpawnedUnit->unitController = UnitController::Player;
	}
	else if (unitType == UnitType::BluePlayer)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(unitBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Blue;
		SpawnedUnit->unitController = UnitController::Player;
	}
	else if (unitType == UnitType::RedOpponent)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(unitBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Red;
		SpawnedUnit->unitController = UnitController::AI;
	}
	else if (unitType == UnitType::GreenOpponent)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(unitBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Green;
		SpawnedUnit->unitController = UnitController::AI;
	}
	else if (unitType == UnitType::BlueOpponent)
	{
		ABaseUnit* SpawnedUnit = World->SpawnActor<ABaseUnit>(unitBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedUnit->currentColorTile = SetInitialUnitTileColor(tileType);
		SpawnedUnit->unitColor = UnitColor::Blue;
		SpawnedUnit->unitController = UnitController::AI;
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
