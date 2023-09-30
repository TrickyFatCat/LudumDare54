// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "MainMenu/MainMenuWidget.h"

#include "ButtonWidget.h"
#include "TransitionScreenWidget.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Quit->OnButtonClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
	Widget_TransitionScreen->OnShowed.AddDynamic(this, &UMainMenuWidget::OnTransitionScreenShowed);
	Widget_TransitionScreen->Hide();
}

void UMainMenuWidget::OnTransitionScreenShowed_Implementation()
{
	if (bMustBeQuit)
	{
		UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
	}
}

void UMainMenuWidget::OnTransitionScreenHidden_Implementation()
{
}

void UMainMenuWidget::QuitGame(UButtonWidget* Button)
{
	bMustBeQuit =  true;
	Widget_TransitionScreen->Show();
}
