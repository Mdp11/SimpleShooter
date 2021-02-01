// Copyrights Mattia De Prisco 2020


#include "ShooterPlayerController.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorldTimerManager().SetTimer(RestarTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
