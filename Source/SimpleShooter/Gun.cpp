// Copyrights Mattia De Prisco 2020

#include "Gun.h"

#include "Kismet/GameplayStatics.h"

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
}

void AGun::BeginPlay()
{
    Super::BeginPlay();
}

void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
