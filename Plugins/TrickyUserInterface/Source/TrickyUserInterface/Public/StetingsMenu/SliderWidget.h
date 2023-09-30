// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "Components/Slider.h"
#include "SliderWidget.generated.h"

class UTextBlock;

/**
 * A slider with a text.
 */
UCLASS()
class TRICKYUSERINTERFACE_API USliderWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category="Slider", meta=(BindWidget))
	TObjectPtr<USlider> Slider_Main = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Slider", meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_Value = nullptr;

	UFUNCTION()
	void ChangeValue(const float Value);

	/**Called when the value changed*/
	UFUNCTION(BlueprintNativeEvent, Category="Slider")
	void HandleValueChange(const float Value);

	virtual void HandleValueChange_Implementation(const float Value);
	
public:
	/**Called when the value changed*/
	UPROPERTY(BlueprintAssignable)
	FOnFloatValueChangedEvent OnValueChanged;
	
	/**Initial value of the slider*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider")
	float InitialValue = 1.0;

	/**Minimum value of the slider*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider")
	float MinValue = 0.0;

	/**Maximum value of the slider*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider")
	float MaxValue = 1.0;

	/**Sets value of the slider*/
	UFUNCTION(BlueprintCallable, Category="Slider")
	void SetValue(const float Value);

private:
	void SetTextValue(const float Value) const;
};
