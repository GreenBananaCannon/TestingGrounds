// //Copyright Adam Tabis

#include "ItemDrop.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemDrop::AItemDrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a Item mesh component
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);	
}

// Called when the game starts or when spawned
void AItemDrop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

