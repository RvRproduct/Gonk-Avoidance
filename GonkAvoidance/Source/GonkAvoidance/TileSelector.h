// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TileSelector.generated.h"

UCLASS()
class GONKAVOIDANCE_API ATileSelector : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATileSelector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
