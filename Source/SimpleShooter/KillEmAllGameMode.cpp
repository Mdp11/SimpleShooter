// Copyrights Mattia De Prisco 2020


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}
}

void AKillEmAllGameMode::EndGame(bool bPlayerWon)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		Controller->IsPlayerController()
			? Controller->GameHasEnded(Controller->GetPawn(), bPlayerWon)
			: Controller->GameHasEnded(Controller->GetPawn(), !bPlayerWon);
	}
}
