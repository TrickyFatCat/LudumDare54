// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "MainMenu/SplashScreenWidget.h"
#include "TransitionScreenWidget.h"
#include "Components/Image.h"
#include "TimerManager.h"

DECLARE_LOG_CATEGORY_CLASS(LogSplashScreen, All, All);

void USplashScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Widget_TransitionScreen->OnHidden.AddDynamic(this, &USplashScreenWidget::StartSplashTimer);
	Widget_TransitionScreen->OnShowed.AddDynamic(this, &USplashScreenWidget::SwitchSplashScreen);

	if (SplashImages.Num() == 0)
	{
		UE_LOG(LogSplashScreen, Warning, TEXT("Splash screen images array is empty."));
		OnSplashFinished.Broadcast();
		return;
	}

	Image_Splash->SetBrushFromTexture(SplashImages[CurrentSplashIndex], true);
	Widget_TransitionScreen->Hide();
}

void USplashScreenWidget::StartSplashTimer()
{
	if (!GetWorld())
	{
		return;
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
	                                       ToRawPtr(Widget_TransitionScreen),
	                                       &UTransitionScreenWidget::Show,
	                                       SplashDuration);
}

void USplashScreenWidget::SwitchSplashScreen()
{
	CurrentSplashIndex++;

	if (CurrentSplashIndex >= SplashImages.Num())
	{
		OnSplashFinished.Broadcast();
		return;
	}

	TObjectPtr<UTexture2D> Texture = SplashImages[CurrentSplashIndex];
	
	if (Texture)
	{
		Image_Splash->SetBrushFromTexture(ToRawPtr(Texture), true);
		OnSplashChanged.Broadcast(CurrentSplashIndex);
	}
	else
	{
		UE_LOG(LogSplashScreen, Warning, TEXT("Splashscreen %d is nullptr. Please, set this splashscreen."), CurrentSplashIndex);
	}

	Widget_TransitionScreen->Hide();
}
