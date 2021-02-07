// Copyrights Mattia De Prisco 2020


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "AI/ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}
	else
	{
		for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
		{
			if(!Controller->IsDead())
			{
				return;
			}
		}
		EndGame(true);
	}
}

void AKillEmAllGameMode::EndGame(bool bPlayerWon) const
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		Controller->IsPlayerController()
			? Controller->GameHasEnded(Controller->GetPawn(), bPlayerWon)
			: Controller->GameHasEnded(Controller->GetPawn(), !bPlayerWon);
	}
}
