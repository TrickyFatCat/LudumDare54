// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "Gameplay/LoseMenuWidget.h"

#include "ButtonWidget.h"
#include "TransitionScreenWidget.h"
#include "Kismet/GameplayStatics.h"

void ULoseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Restart && Button_Quit)
	{
		Button_Restart->OnButtonClicked.AddDynamic(this, &ULoseMenuWidget::OnButtonClicked);
		Button_Quit->OnButtonClicked.AddDynamic(this, &ULoseMenuWidget::OnButtonClicked);
	}

	if (Widget_TransitionScreen)
	{
		Widget_TransitionScreen->OnShowed.AddDynamic(this, &ULoseMenuWidget::HandleTransitionShowed);
		Widget_TransitionScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULoseMenuWidget::OnButtonClicked_Implementation(UButtonWidget* Button)
{
	ClickedButton = Button;
	Widget_TransitionScreen->Show();
}

void ULoseMenuWidget::Restart_Implementation()
{
	const FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void ULoseMenuWidget::Quit_Implementation()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void ULoseMenuWidget::HandleTransitionShowed_Implementation()
{
	if (ClickedButton == Button_Restart)
	{
		Restart();
	}
	else if (ClickedButton == Button_Quit)
	{
		Quit();
	}
}
