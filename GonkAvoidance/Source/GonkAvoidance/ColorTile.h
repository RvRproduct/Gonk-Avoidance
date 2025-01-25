// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTile.h"
#include "ColorTile.generated.h"

UCLASS()
class GONKAVOIDANCE_API AColorTile : public ABaseTile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
