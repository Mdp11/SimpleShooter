// Copyrights Mattia De Prisco 2020

#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Characters/ShooterCharacter.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	OwnerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	const FVector BulletEndPoint = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * MaxRange;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	const bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewPointLocation, BulletEndPoint,
	                                                              ECC_GameTraceChannel1, CollisionQueryParams);
	if (bHitSuccess)
	{
		FVector ShotDirection = PlayerViewPointRotation.GetInverse().Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location,
		                                         ShotDirection.Rotation());

		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit)
		{
			FPointDamageEvent DamageEvent{Damage, HitResult, ShotDirection, nullptr};
			ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);	
		}

	}
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
