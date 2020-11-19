// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"

#include "Kismet/GameplayStatics.h"

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
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction(TEXT("SwitchSpeed"), IE_Pressed, this, &AShooterCharacter::SwitchSpeed);
    PlayerInputComponent->BindAction(TEXT("SwitchSpeed"), IE_Released, this, &AShooterCharacter::SwitchSpeed);
    PlayerInputComponent->BindAction(TEXT("SwitchDefaultSpeed"), IE_Released, this, &AShooterCharacter::SwitchDefaultSpeed);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
    PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
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
