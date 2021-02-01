// Copyrights Mattia De Prisco 2020


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass, TEXT("LoseScreen"));
	if (LoseScreen)
	{
		LoseScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestarTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

float AShooterPlayerController::GetRestartDelay() const
{
	return RestartDelay;
}
