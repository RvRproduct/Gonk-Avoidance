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

UCLASS()
class GONKAVOIDANCE_API ABaseTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTile();

	TileType tileType = TileType::None;
	bool validTile = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
