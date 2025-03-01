// Copyrights Mattia De Prisco 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

	public:
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
};
