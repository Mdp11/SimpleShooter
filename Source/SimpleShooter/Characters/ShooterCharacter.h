// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AShooterCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(EditAnywhere, Category="ControllerMovement")
    float RotationRate = 50.f;

    float SpeedModifier{RunningSpeedMultiplier};
    const float RunningSpeedMultiplier = 1.2f;
    const float WalkingSpeedMultiplier = 4.f;

    UPROPERTY(EditAnywhere, Category="Camera")
    USpringArmComponent* SpringArmComponent{nullptr};

    UPROPERTY(EditAnywhere, Category="Camera")
    UCameraComponent* CameraComponent{nullptr};

    void MoveForward(const float AxisValue);
    void MoveRight(const float AxisValue);
    void LookUpRate(const float AxisValue);
    void LookRightRate(const float AxisValue);
    void IncreaseSpeed();
    void RestoreSpeed();
};
