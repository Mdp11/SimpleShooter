// Copyrights Mattia De Prisco 2020


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	Hud->RemoveFromViewport();

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass, TEXT("WinScreen"));
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass, TEXT("LoseScreen"));
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

float AShooterPlayerController::GetRestartDelay() const
{
	return RestartDelay;
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Hud = CreateWidget(this, HudClass, TEXT("HUD"));
	if (Hud)
	{
		Hud->AddToViewport();
	}
}
