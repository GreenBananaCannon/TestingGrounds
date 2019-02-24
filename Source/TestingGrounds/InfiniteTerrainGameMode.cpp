// //Copyright Adam Tabis

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "NavMesh/NavMeshBoundsVolume.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(TEXT("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	//TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Initially adding actors to pool: %s"), *VolumeToAdd->GetName());
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}