// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"


#include "ShooterCharacter.generated.h"

class AGun;

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

    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
    UPROPERTY(EditAnywhere, Category="ControllerMovement")
    float RotationRate = 50.f;

    float SpeedModifier{};
    float DefaultSpeedModifier = 1.f;
    float AlternateSpeedModifier = 0.3f;

    UPROPERTY(EditAnywhere, Category="Camera")
    USpringArmComponent* SpringArmComponent{nullptr};

    UPROPERTY(EditAnywhere, Category="Camera")
    UCameraComponent* CameraComponent{nullptr};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AGun> GunClass;

    UPROPERTY()
    AGun* Gun;

    UPROPERTY(EditDefaultsOnly)
    float MaxHealth{100.f};

    UPROPERTY(VisibleAnywhere)
    float Health;

    void MoveForward(const float AxisValue);
    void MoveRight(const float AxisValue);
    
    void LookUpRate(const float AxisValue);
    void LookRightRate(const float AxisValue);
    
    void SwitchSpeed();
    void SwitchDefaultSpeed();

    void PullTrigger();
    
};
