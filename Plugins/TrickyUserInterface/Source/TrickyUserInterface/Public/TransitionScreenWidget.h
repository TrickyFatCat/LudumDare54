// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "TransitionScreenWidget.generated.h"

class UImage;
/**
 * A widget which allows to create a smooth transition screen.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API UTransitionScreenWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TransitionScreen", meta=(BindWidget))
	TObjectPtr<UImage> Image_Transition = nullptr;
};
