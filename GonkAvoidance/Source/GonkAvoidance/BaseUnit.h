// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

class AMapCreator;

UCLASS()
class GONKAVOIDANCE_API ABaseUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseUnit();

	// Unit Controller By (AI, Player, PlayerTwo)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Controller Type")
	UnitController unitController = UnitController::None;

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


	// Get all of the Tiles from the Map Creator
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Creator")
	AMapCreator* mapCreator;

	// For A* Path Finding
	TArray<ABaseTile*> setPathToTileTarget;
	TArray<TPair<ABaseTile*, TilePathFinding*>> openPathToTileTarget;
	TArray<TPair<ABaseTile*, TilePathFinding*>> closedPathToWaypointTarget;
	TPair<ABaseTile*, TilePathFinding*> startPathTile;
	TPair<ABaseTile*, TilePathFinding*> goalPathTile;
	TPair<ABaseTile*, TilePathFinding*> lastPathWaypoint;
	ABaseTile* parentTile;

	bool tilePathDone = false;
	bool hasStartedSearch = false;
	bool hasReachedDestination = true;

	// For The Seek
	UPROPERTY(VisibleAnywhere, Category = "Current Tile")
	ABaseTile* currentTile;

	UPROPERTY(VisibleAnywhere, Category = "Next Tile")
	ABaseTile* nextTile;

	UPROPERTY(VisibleAnywhere, Category = "Player Units")
	TArray<ABaseUnit*> playerUnits;

	UPROPERTY(VisibleAnywhere, Category = "Opponent Units")
	TArray<ABaseUnit*> opponentUnits;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ClearTilePath();
	void BeginSearchTilePath();
	void SearchTilePath(TPair<ABaseTile*, TilePathFinding*> thisPathTile);
	bool UpdateTile(ABaseTile* neighborTile, float G, float H, float F, TPair<ABaseTile*, TilePathFinding*> parentPathTile);
	void SetTileGHF(TPair<ABaseTile*, TilePathFinding*> thisPathTile, ABaseTile* neighborTile, ABaseTile* goalTile);
	bool IsClosedTile(ABaseTile* thisTile);
	ABaseTile* GetClosestPossibleTileToPlayer();
	void SetWaypointPath();

};
