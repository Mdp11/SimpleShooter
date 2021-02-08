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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShotDirection;
	
	bool bHitSuccess = GunTrace(HitResult, ShotDirection);

	if (bHitSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location,
                                                 ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, HitResult.Location, ShotDirection.Rotation());

		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit)
		{
			AController* OwnerController = GetOwnerController();
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

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(!OwnerController)
	{
		return false;
	}

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	

	OwnerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	ShotDirection = PlayerViewPointRotation.GetInverse().Vector();

	const FVector BulletEndPoint = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * MaxRange;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewPointLocation, BulletEndPoint,
                                                                  ECC_GameTraceChannel1, CollisionQueryParams);
}

AController* AGun::GetOwnerController() const
{
	AController* OwnerController = nullptr;
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		OwnerController = OwnerPawn->GetController();
	}

	return OwnerController;
}
