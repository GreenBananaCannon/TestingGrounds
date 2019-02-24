// //Copyright Adam Tabis

#include "ActorPool.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Checkout()
{
	AActor* ActorToCheckout = nullptr;
	if (NavPool.Num() > 0)
	{
		ActorToCheckout = NavPool.Pop(true);
		UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out %s"), *GetName(), *ActorToCheckout->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Pool is empty"));
	}
	
	if (!ensure(ActorToCheckout)) { return nullptr; }
	return ActorToCheckout;
}

void UActorPool::Return(AActor* ActorToReturn)
{
	if (!ensure(ActorToReturn)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("[%s] Returning Actor %s "), *GetName(), *ActorToReturn->GetName());
	NavPool.Add(ActorToReturn);
}

void UActorPool::Add(AActor* ActorToAdd)
{
	if (!ensure(ActorToAdd)) { return; }
	NavPool.Add(ActorToAdd);
}
