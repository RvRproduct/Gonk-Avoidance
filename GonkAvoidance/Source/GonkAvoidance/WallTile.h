// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTile.h"
#include "WallTile.generated.h"

UCLASS()
class GONKAVOIDANCE_API AWallTile : public ABaseTile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallTile();

	TileType tileType = TileType::Wall;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
