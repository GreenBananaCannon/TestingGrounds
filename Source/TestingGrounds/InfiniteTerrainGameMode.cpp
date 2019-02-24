// //Copyright Adam Tabis

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"

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

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found Actor %s"), *VolumeToAdd->GetName());
}