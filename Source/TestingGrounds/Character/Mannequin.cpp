// //Copyright Adam Tabis

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/Gun.h"
#include "Weapons/BallProjectile.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "Components/InputComponent.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FPCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FPCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (IsPlayerControlled()) // attach depending on who is controlling the pawns
	{
		//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
		if (!ensure(GunBlueprint)) { return; }
		Gun = GetWorld()->SpawnActor<AGun>(
			GunBlueprint,
			Mesh1P->GetSocketLocation(FName("GripPoint")),
			Mesh1P->GetSocketRotation(FName("GripPoint"))
			);
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	
		FActorSpawnParameters SpawnParams = FActorSpawnParameters();
		SpawnParams.Name = FName("NPCGun", GetUniqueID());
		if (!ensure(GunBlueprint)) { return; }
		Gun = GetWorld()->SpawnActor<AGun>(
			GunBlueprint,
			Mesh1P->GetSocketLocation(FName("GripPoint")),
			Mesh1P->GetSocketRotation(FName("GripPoint")),
			SpawnParams
			);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}

	Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();

	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

void AMannequin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Gun->Destroy();
}

void AMannequin::PullTrigger()
{
	Gun->OnFire();
}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();
	if (!ensure(Gun)) { return;  }
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision); //prevent invisible 1P models from causing collisions
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{  
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	
}

