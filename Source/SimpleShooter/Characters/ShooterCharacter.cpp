// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"

#include "Kismet/GameplayStatics.h"

AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
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
    PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AShooterCharacter::IncreaseSpeed);
    PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &AShooterCharacter::RestoreSpeed);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
    PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
}

void AShooterCharacter::MoveForward(const float AxisValue)
{
    AddMovementInput(GetActorForwardVector(), AxisValue / SpeedModifier);
}

void AShooterCharacter::MoveRight(const float AxisValue)
{
    AddMovementInput(GetActorRightVector(), AxisValue / SpeedModifier);
}

void AShooterCharacter::LookUpRate(const float AxisValue)
{
    AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(const float AxisValue)
{
    AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::IncreaseSpeed()
{
    SpeedModifier = RunningSpeedMultiplier;
}

void AShooterCharacter::RestoreSpeed()
{
    SpeedModifier = WalkingSpeedMultiplier;
}
