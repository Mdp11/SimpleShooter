// Copyrights Mattia De Prisco 2020

#include "ShooterCharacter.h"


#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Gun.h"

AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    SpeedModifier = DefaultSpeedModifier;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void AShooterCharacter::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
    Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Gun->SetOwner(this);
}

bool AShooterCharacter::IsDead() const
{
    return Health == 0.f;
}

void AShooterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);

    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
    PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

    PlayerInputComponent->BindAction(TEXT("SwitchSpeed"), IE_Pressed, this, &AShooterCharacter::SwitchSpeed);
    PlayerInputComponent->BindAction(TEXT("SwitchSpeed"), IE_Released, this, &AShooterCharacter::SwitchSpeed);
    PlayerInputComponent->BindAction(TEXT("SwitchDefaultSpeed"), IE_Released, this, &AShooterCharacter::SwitchDefaultSpeed);

    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);

    PlayerInputComponent->BindAction(TEXT("PullTrigger"), IE_Pressed, this, &AShooterCharacter::PullTrigger);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
    AActor* DamageCauser)
{
    const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health = FMath::Clamp(Health - DamageTaken, 0.f, MaxHealth);

    if(IsDead())
    {
        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    
    return DamageTaken;
}

void AShooterCharacter::MoveForward(const float AxisValue)
{
    const float Modifier = FMath::IsNearlyEqual(AxisValue, 350.f, 1) ? 1 : SpeedModifier;
    AddMovementInput(GetActorForwardVector(), AxisValue * Modifier);
}

void AShooterCharacter::MoveRight(const float AxisValue)
{
    const float Modifier = FMath::IsNearlyEqual(AxisValue, 350.f, 1) ? 1 : SpeedModifier;
    AddMovementInput(GetActorRightVector(), AxisValue * Modifier);
}

void AShooterCharacter::LookUpRate(const float AxisValue)
{
    AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(const float AxisValue)
{
    AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::SwitchSpeed()
{
    SpeedModifier = FMath::IsNearlyEqual(SpeedModifier, AlternateSpeedModifier)
                        ? DefaultSpeedModifier
                        : AlternateSpeedModifier;
}

void AShooterCharacter::SwitchDefaultSpeed()
{
    Swap(DefaultSpeedModifier, AlternateSpeedModifier);
    SwitchSpeed();
}

void AShooterCharacter::PullTrigger()
{
    Gun->PullTrigger();
}
