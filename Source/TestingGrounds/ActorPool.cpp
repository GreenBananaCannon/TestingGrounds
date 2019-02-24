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
	UE_LOG(LogTemp, Warning, TEXT("NavPool size before Checkout occurs: %d"), NavPool.Num());
	if (NavPool.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Pool is empty"));
		return nullptr;
	}
	return NavPool.Pop();;
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
	NavPool.Push(ActorToAdd);
}
