// //Copyright Adam Tabis

#include "RadialProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Public/TimerManager.h"

// Sets default values
ARadialProjectile::ARadialProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ARadialProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Launch particles
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->SetupAttachment(RootComponent);

	// Impact blast particles
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->SetupAttachment(RootComponent);
	ImpactBlast->bAutoActivate = false;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 6000.f;
	ProjectileMovement->MaxSpeed = 6000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}

void ARadialProjectile::OnTimerExpire()
{
	Destroy();
}

void ARadialProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics && OtherComponent->IsSimulatingPhysics()
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL))
	{
		LaunchBlast->Deactivate();
		

		//OtherComponent->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		
		auto DamageApplied = UGameplayStatics::ApplyRadialDamage(
			this,
			ProjectileDamage,
			GetActorLocation(),
			500.0f, // for consistency between the explosion and damage application
			UDamageType::StaticClass(),
			TArray<AActor*>(), // damage all actors, do not ignore any
			this,
			GetWorld()->GetFirstPlayerController(),
			true
		);
		ImpactBlast->Activate();
		UE_LOG(LogTemp, Warning, TEXT("Was Radial Damage Applied?: %d to %s"), DamageApplied, *Hit.GetActor()->GetName());

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARadialProjectile::OnTimerExpire, DestroyDelay, false);
		CollisionComp->DestroyComponent();
	}
}

