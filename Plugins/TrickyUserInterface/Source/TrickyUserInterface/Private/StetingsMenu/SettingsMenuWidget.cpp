// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "StetingsMenu/SettingsMenuWidget.h"

#include "ButtonWidget.h"
#include "TrickyUserInterfaceLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "StetingsMenu/SliderWidget.h"


void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	const int32 QualityIndex = UserSettings->GetViewDistanceQuality();

	if (Slider_ResolutionScale)
	{
		Slider_ResolutionScale->OnValueChanged.AddDynamic(this, &USettingsMenuWidget::ApplyResolutionScale);
		Slider_ResolutionScale->SetValue(UserSettings->GetResolutionScaleNormalized());
	}

	if (Button_Quality_Low && Button_Quality_Medium && Button_Quality_High && Button_Quality_Epic)
	{
		Button_Quality_Low->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyQuality);
		Button_Quality_Medium->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyQuality);
		Button_Quality_High->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyQuality);
		Button_Quality_Epic->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyQuality);

		switch (QualityIndex)
		{
		case 0:
			Button_Quality_Low->SetIsEnabled(false);
			CurrentQualityButton = Button_Quality_Low;
			break;

		case 1:
			Button_Quality_Medium->SetIsEnabled(false);
			CurrentQualityButton = Button_Quality_Medium;
			break;

		case 2:
			Button_Quality_High->SetIsEnabled(false);
			CurrentQualityButton = Button_Quality_High;
			break;

		case 3:
			Button_Quality_Epic->SetIsEnabled(false);
			CurrentQualityButton = Button_Quality_Epic;
			break;
		}
	}

	if (Button_ScreenMode_Window && Button_ScreenMode_Full)
	{
		Button_ScreenMode_Window->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyScreenMode);
		Button_ScreenMode_Full->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyScreenMode);


		const EWindowMode::Type WindowMode = UserSettings->GetDefaultWindowMode();

		switch (WindowMode)
		{
		case EWindowMode::Fullscreen:
		case EWindowMode::WindowedFullscreen:
			Button_ScreenMode_Full->SetIsEnabled(false);
			CurrentScreenModeButton = Button_ScreenMode_Full;
			break;

		case EWindowMode::Windowed:
			Button_ScreenMode_Window->SetIsEnabled(false);
			CurrentScreenModeButton = Button_ScreenMode_Window;
			break;
		}
	}
}

void USettingsMenuWidget::ApplyQuality(UButtonWidget* ButtonWidget)
{
	if (!ButtonWidget)
	{
		return;
	}

	int32 QualityIndex = 0;

	if (ButtonWidget == Button_Quality_Low)
	{
		QualityIndex = 0;
	}
	else if (ButtonWidget == Button_Quality_Medium)
	{
		QualityIndex = 1;
	}
	else if (ButtonWidget == Button_Quality_High)
	{
		QualityIndex = 2;
	}
	else if (ButtonWidget == Button_Quality_Epic)
	{
		QualityIndex = 3;
	}

	UTrickyUserInterfaceLibrary::SetQualitySettings(QualityIndex);
	ButtonWidget->SetIsEnabled(false);
	CurrentQualityButton->SetIsEnabled(true);
	CurrentQualityButton = ButtonWidget;
}

void USettingsMenuWidget::ApplyScreenMode(UButtonWidget* ButtonWidget)
{
	if (!ButtonWidget)
	{
		return;
	}

	EWindowMode::Type WindowMode = EWindowMode::Fullscreen;

	if (ButtonWidget == Button_ScreenMode_Window)
	{
		WindowMode = EWindowMode::Windowed;
	}

	UTrickyUserInterfaceLibrary::SetScreenMode(WindowMode);
	ButtonWidget->SetIsEnabled(false);
	CurrentScreenModeButton->SetIsEnabled(true);
	CurrentScreenModeButton = ButtonWidget;
}

void USettingsMenuWidget::ApplyResolutionScale(const float Value)
{
	if (!IsValid(Slider_ResolutionScale))
	{
		return;
	}

	UTrickyUserInterfaceLibrary::SetResolutionScale(Value);
}
