// Copyrights Mattia De Prisco 2020


#include "ShooterAIController.h"


#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if(ControlledCharacter)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		BlackboardComponent->SetValueAsVector(TEXT("StartLocation"),
		                                      GetPawn()->GetActorLocation());
	}
}
