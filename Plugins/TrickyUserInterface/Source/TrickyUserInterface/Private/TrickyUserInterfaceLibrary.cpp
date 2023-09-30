// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "TrickyUserInterfaceLibrary.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetMathLibrary.h"

void UTrickyUserInterfaceLibrary::SetQualitySettings(const int32 QualityIndex)
{
	if (QualityIndex < 0 || QualityIndex > 3)
	{
		return;
	}

	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();

	UserSettings->SetViewDistanceQuality(QualityIndex);
	UserSettings->SetAntiAliasingQuality(QualityIndex);
	UserSettings->SetPostProcessingQuality(QualityIndex);
	UserSettings->SetShadowQuality(QualityIndex);
	UserSettings->SetGlobalIlluminationQuality(QualityIndex);
	UserSettings->SetReflectionQuality(QualityIndex);
	UserSettings->SetTextureQuality(QualityIndex);
	UserSettings->SetFoliageQuality(QualityIndex);
	UserSettings->SetVisualEffectQuality(QualityIndex);
	UserSettings->SetShadingQuality(QualityIndex);

	UserSettings->ApplySettings(false);
}

void UTrickyUserInterfaceLibrary::SetScreenMode(EWindowMode::Type ScreenMode)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	UserSettings->SetFullscreenMode(ScreenMode);

	FIntPoint DesktopResolution = UserSettings->GetDesktopResolution();

	if (ScreenMode == EWindowMode::Windowed)
	{
		DesktopResolution.X *= 0.75;
		DesktopResolution.Y *= 0.75;
	}

	UserSettings->SetScreenResolution(DesktopResolution);
	UserSettings->ApplySettings(false);
	UserSettings->ApplyResolutionSettings(false);
}

void UTrickyUserInterfaceLibrary::SetResolutionScale(const float Scale)
{
	if (Scale < 0.f || Scale > 1.0)
	{
		return;
	}

	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();

	UserSettings->SetResolutionScaleNormalized(Scale);
	UserSettings->ApplySettings(false);
}

void UTrickyUserInterfaceLibrary::SetResolution(const int32 Width, const int32 Height)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	const FIntPoint Resolution{Width, Height};
	UserSettings->SetScreenResolution(Resolution);
	UserSettings->ApplyResolutionSettings(false);
}

FString UTrickyUserInterfaceLibrary::ConvertTimeSeconds(const float TimeSeconds, const EFormatTime TimeFormat)
{
	const FTimespan Timespan = UKismetMathLibrary::FromSeconds(TimeSeconds);

	FString Result = "";

	const int32 TotalMinutes = static_cast<int32>(Timespan.GetTotalMinutes());
	const int32 Seconds = Timespan.GetSeconds();
	const int32 TotalSeconds = (FMath::CeilToInt(Timespan.GetTotalSeconds()));
	const int32 Milliseconds = Timespan.GetFractionMilli();

	auto ConvertMilliseconds = [&Milliseconds](const float Fraction) -> int32
	{
		return static_cast<int32>(Milliseconds * Fraction);
	};

	switch (TimeFormat)
	{
	case EFormatTime::MM_SS_MsMs:
		Result = FString::Printf(TEXT("%02d:%02d.%02d"),
		                         TotalMinutes,
		                         Seconds,
		                         ConvertMilliseconds(0.1f));
		break;

	case EFormatTime::MM_SS_Ms:
		Result = FString::Printf(TEXT("%02d:%02d.%d"),
		                         TotalMinutes,
		                         Seconds,
		                         ConvertMilliseconds(0.01f));
		break;

	case EFormatTime::MM_SS:
		Result = FString::Printf(TEXT("%02d:%02d"), TotalMinutes, Seconds);
		break;

	case EFormatTime::SS_MsMs:
		Result = FString::Printf(TEXT("%02d.%02d"), TotalSeconds, ConvertMilliseconds(0.1f));
		break;

	case EFormatTime::SS_Ms:
		Result = FString::Printf(TEXT("%02d.%d"), TotalSeconds, ConvertMilliseconds(0.01f));
		break;

	case EFormatTime::SS:
		Result = FString::Printf(TEXT("%02d"), TotalSeconds);
		break;
	}

	return Result;
}
