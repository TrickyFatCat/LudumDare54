// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "StetingsMenu/SoundSliderWidget.h"

#include "Kismet/GameplayStatics.h"

void USoundSliderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Slider_Main)
	{
		SetSoundVolume(Slider_Main->GetValue());
	}
}

void USoundSliderWidget::HandleValueChange_Implementation(const float Value)
{
	SetSoundVolume(Value);
}

void USoundSliderWidget::SetSoundVolume(const float Value) const
{
	if (!SoundMix || !SoundClass)
	{
		return;
	}
	
	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundClass, Value);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);
}
