// Copyrights Mattia De Prisco 2020


#include "ShooterAIController.h"


#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (LineOfSightTo(PlayerPawn))
	{
		BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"),
		                                      UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
		BlackboardComponent->SetValueAsVector(TEXT("PlayerLastKnownLocation"),
		                                      UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
	}
	else
	{
		BlackboardComponent->ClearValue("PlayerLocation");
	}
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
