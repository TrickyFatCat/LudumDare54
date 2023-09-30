// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "Gameplay/WinMenuWidget.h"

#include "ButtonWidget.h"
#include "TransitionScreenWidget.h"
#include "Kismet/GameplayStatics.h"

void UWinMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Continue && Button_Restart && Button_Quit)
	{
		Button_Continue->OnButtonClicked.AddDynamic(this, &UWinMenuWidget::OnButtonClicked);
		Button_Restart->OnButtonClicked.AddDynamic(this, &UWinMenuWidget::OnButtonClicked);
		Button_Quit->OnButtonClicked.AddDynamic(this, &UWinMenuWidget::OnButtonClicked);
	}

	if (Widget_TransitionScreen)
	{
		Widget_TransitionScreen->OnShowed.AddDynamic(this, &UWinMenuWidget::HandleTransitionShowed);
		Widget_TransitionScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWinMenuWidget::OnButtonClicked_Implementation(UButtonWidget* Button)
{
	ClickedButton = Button;
	Widget_TransitionScreen->Show();
}

void UWinMenuWidget::Continue_Implementation()
{
	const FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void UWinMenuWidget::Restart_Implementation()
{
	const FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void UWinMenuWidget::Quit_Implementation()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UWinMenuWidget::HandleTransitionShowed_Implementation()
{
	if (ClickedButton == Button_Continue)
	{
		Continue();
	}
	else if (ClickedButton == Button_Restart)
	{
		Restart();
	}
	else if (ClickedButton == Button_Quit)
	{
		Quit();
	}
}
