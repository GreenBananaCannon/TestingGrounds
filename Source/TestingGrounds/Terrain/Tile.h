// //Copyright Adam Tabis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 300.0f, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	void PositionNavMeshBoundsVolume();

	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLocation,float Radius);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;

};
