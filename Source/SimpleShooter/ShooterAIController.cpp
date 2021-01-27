// Copyrights Mattia De Prisco 2020


#include "ShooterAIController.h"


#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// UE_LOG(LogTemp, Warning, TEXT("TICKO"));
	//
	// AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//
	// if (LineOfSightTo(PlayerPawn))
	// {
	// 	MoveToActor(PlayerPawn, 100.f);
	// 	SetFocus(PlayerPawn);
	// }
	// else
	// {
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	StopMovement();
	// }
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		BlackboardComponent->SetValueAsVector("PlayerLocation",
		                                      UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
		BlackboardComponent->SetValueAsVector("StartLocation",
		                                      GetPawn()->GetActorLocation());
	}
}
