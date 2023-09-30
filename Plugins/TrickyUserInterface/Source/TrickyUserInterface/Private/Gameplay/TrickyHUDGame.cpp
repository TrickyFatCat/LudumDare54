// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "Gameplay/TrickyHUDGame.h"

#include "BaseUserWidget.h"
#include "TrickyGameModeBase.h"

void ATrickyHUDGame::BeginPlay()
{
	Super::BeginPlay();

	CreateUserWidget(EGameModeState::Inactive, InactiveStateWidget);
	CreateUserWidget(EGameModeState::Preparation, PreparationScreenWidget);
	CreateUserWidget(EGameModeState::InProgress, GameplayScreenWidget);
	CreateUserWidget(EGameModeState::Pause, PauseScreenWidget);
	CreateUserWidget(EGameModeState::Win, WinScreenWidget);
	CreateUserWidget(EGameModeState::Lose, LoseScreenWidget);
	CreateUserWidget(EGameModeState::Transition, TransitionScreenWidget);

	
	for (const auto WidgetPair : UserWidgets)
	{
		UBaseUserWidget* UserWidget = WidgetPair.Value;

		if (!UserWidget)
		{
			continue;
		}

		UserWidget->AddToViewport();
		UserWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		TObjectPtr<ATrickyGameModeBase> GameMode = Cast<ATrickyGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnStateChanged.AddDynamic(this, &ATrickyHUDGame::OnGameModeSessionChanged);
		}
	}
}

void ATrickyHUDGame::OnGameModeSessionChanged(EGameModeState NewState)
{
	if (ActiveWidget)
	{
		ActiveWidget->Hide();
	}

	if (!UserWidgets.Contains(NewState))
	{
		return;
	}

	ActiveWidget = UserWidgets[NewState];
	ActiveWidget->Show();
}

void ATrickyHUDGame::CreateUserWidget(const EGameModeState State, TSubclassOf<UBaseUserWidget> WidgetClass)
{
	if (!WidgetClass)
	{
		return;
	}

	UserWidgets.Add(State, ToObjectPtr(CreateWidget<UBaseUserWidget>(GetWorld(), WidgetClass)));
}
