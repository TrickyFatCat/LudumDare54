// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "SliderWidget.h"
#include "SoundSliderWidget.generated.h"

class USoundClass;
class USoundMix;

/**
 * A slider widget created specifically to control sound volume in options
 */
UCLASS()
class TRICKYUSERINTERFACE_API USoundSliderWidget : public USliderWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, Category="Slider")
	USoundClass* SoundClass = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Slider")
	USoundMix* SoundMix = nullptr;
	
	virtual void HandleValueChange_Implementation(const float Value) override;

	void SetSoundVolume(const float Value) const;
};

