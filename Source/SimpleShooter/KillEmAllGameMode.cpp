// Copyrights Mattia De Prisco 2020


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if(PlayerController)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
}
