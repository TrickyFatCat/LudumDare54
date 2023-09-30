// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "StetingsMenu/SliderWidget.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"

void USliderWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Slider_Main)
	{
		Slider_Main->SetValue(InitialValue);
		Slider_Main->SetMinValue(MinValue);
		Slider_Main->SetMaxValue(MaxValue);
		SetTextValue(InitialValue);
	}
}

void USliderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(Slider_Main))
	{
		Slider_Main->OnValueChanged.AddDynamic(this, &USliderWidget::ChangeValue);
	}
}

void USliderWidget::ChangeValue(const float Value)
{
	OnValueChanged.Broadcast(Value);
	SetTextValue(Value);
	HandleValueChange(Value);
}

void USliderWidget::HandleValueChange_Implementation(const float Value)
{
}

void USliderWidget::SetValue(const float Value)
{
	if (!IsValid(Slider_Main))
	{
		return;
	}
	
	Slider_Main->SetValue(Value);
	SetTextValue(Value);
}

void USliderWidget::SetTextValue(const float Value) const
{
	if (!IsValid(Text_Value))
	{
		return;
	}
	
	const FString Text = FString::Printf(TEXT("%.2f"), Value);
	Text_Value->SetText(FText::FromString(Text));
}
