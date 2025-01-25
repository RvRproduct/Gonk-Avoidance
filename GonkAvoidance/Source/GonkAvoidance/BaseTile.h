// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTile.generated.h"

UENUM(BlueprintType)
enum class TileType : uint8
{
	None,
	Wall,
	Red,
	Green,
	Blue
};

UENUM(BlueprintType)
enum class UnitType : uint8
{
	None,
	RedPlayer,
	GreenPlayer,
	BluePlayer,
	RedOpponent,
	GreenOpponent,
	BlueOpponent
};

UCLASS()
class GONKAVOIDANCE_API ABaseTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTile();

	// Can a Unit be on this Tile or Cross this tile
	bool validTile = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile Type")
	TileType tileType = TileType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Units")
	UnitType unitType = UnitType::None;

	UPROPERTY(VisibleAnywhere, Category = "Tile Left")
	ABaseTile* leftTile;

	UPROPERTY(VisibleAnywhere, Category = "Tile Right")
	ABaseTile* rightTile;

	UPROPERTY(VisibleAnywhere, Category = "Tile Up")
	ABaseTile* upTile;

	UPROPERTY(VisibleAnywhere, Category = "Tile Down")
	ABaseTile* downTile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
