// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameManager.h"
#include "BaseTile.h"
#include "BaseUnit.generated.h"

UENUM(BlueprintType)
enum class Combat : uint8
{
	None,
	Attack,
	Strike,
	Charge,
	Defend,
	Counter,
	Evade
};

UENUM(BlueprintType)
enum class CurrentTileColor : uint8
{
	None,
	Red,
	Green,
	Blue
};

UENUM(BlueprintType)
enum class UnitColor : uint8
{
	None,
	Red,
	Green,
	Blue
};

UENUM(BlueprintType)
enum class UnitController : uint8
{
	None,
	AI,
	Player,
	PlayerTwo
};

struct TilePathFinding
{
	float G = 0.0f;
	float H = 0.0f;
	float F = 0.0f;

	ABaseTile* parentTile;
	TilePathFinding* parentTileFinding;
};

class AGameManager;

UCLASS()
class GONKAVOIDANCE_API ABaseUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseUnit();

	// Active Unit
	bool activeUnit = false;

	// Is the Unit Setup
	bool unitSetup = false;

	ABaseTile* playerTargetTile = nullptr;

	bool undoActive = false;
	bool redoActive = false;
	bool moveState = true;

	// Unit Controller By (AI, Player, PlayerTwo)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Controller Type")
	UnitController unitController;

	// Unit Color and Current Tile Color
	CurrentTileColor currentColorTile = CurrentTileColor::None;
	UnitColor unitColor = UnitColor::None;

	// Combat Choice
	Combat combatChoice = Combat::None;

	// Stats
	int tileMovementRange = 6;
	int health = 100;
	int attackPower = 10;
	int defensePower = 5;
	float evasionRate = 30.0f;

	int combatPowerBoost = 2;	
	float hitRateBoost = 25.0f;


	// For A* Path Finding
	UPROPERTY(VisibleAnywhere, Category = "Path To Target")
	TArray<ABaseTile*> setPathToTileTarget;

	UPROPERTY(VisibleAnywhere, Category = "Undo path")
	TArray<ABaseTile*> undoPath;

	UPROPERTY(VisibleAnywhere, Category = "Redo Path")
	TArray<ABaseTile*> redoPath;

	TArray<TPair<ABaseTile*, TilePathFinding*>> openPathToTileTarget;
	TArray<TPair<ABaseTile*, TilePathFinding*>> closedPathToTileTarget;
	TPair<ABaseTile*, TilePathFinding*> startPathTile;
	TPair<ABaseTile*, TilePathFinding*> goalPathTile;
	TPair<ABaseTile*, TilePathFinding*> lastPathTile;
	ABaseTile* parentTile;

	bool tilePathDone = false;
	bool hasStartedSearch = false;
	bool hasReachedDestination = true;
	bool hasSelectedMovement = false;

	// For The Seek
	UPROPERTY(VisibleAnywhere, Category = "Current Tile")
	ABaseTile* currentTile;

	UPROPERTY(VisibleAnywhere, Category = "Next Tile")
	ABaseTile* nextTile;

	UPROPERTY(VisibleAnywhere, Category = "Player Units")
	TArray<ABaseUnit*> playerUnits;

	UPROPERTY(VisibleAnywhere, Category = "Opponent Units")
	TArray<ABaseUnit*> opponentUnits;

	UPROPERTY(VisibleAnywhere, Category = "Max Speed")
	float maxSpeed = 600.0f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector currentVelocity = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category = "Game Manager")
	AGameManager* gameManager;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Seek(FVector tilePosition, float DeltaTime);

	void ClearTilePath();
	void BeginSearchTilePath();
	void SearchTilePath(TPair<ABaseTile*, TilePathFinding*> thisPathTile);
	bool UpdateTile(ABaseTile* neighborTile, float G, float H, float F, TPair<ABaseTile*, TilePathFinding*> parentPathTile);
	void SetTileGHF(TPair<ABaseTile*, TilePathFinding*> thisPathTile, ABaseTile* neighborTile, ABaseTile* goalTile);
	bool IsClosedTile(ABaseTile* thisTile);
	void SetTilePath();

};
