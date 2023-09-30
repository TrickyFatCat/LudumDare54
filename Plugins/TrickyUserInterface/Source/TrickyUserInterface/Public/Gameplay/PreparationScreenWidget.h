// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "PreparationScreenWidget.generated.h"

class UTransitionScreenWidget;
class UTextBlock;

/**
 * A widget for creation of a simple preparation screen with a timer before the game started.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API UPreparationScreenWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PreparationScreen", meta=(BindWidget))
	TObjectPtr<UTransitionScreenWidget> Widget_TransitionScreen = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PreparationScreen", meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_PreparationTimer = nullptr;
};
