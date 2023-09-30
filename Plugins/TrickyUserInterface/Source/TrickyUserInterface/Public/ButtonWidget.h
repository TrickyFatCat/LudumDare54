// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "ButtonWidget.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedSignature, class UButtonWidget*, Button);

/**
 * A a base widget for button creation. Use this widget to create custom buttons in your game.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API UButtonWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	/**Called when Button_Main is clicked.*/
	UPROPERTY(BlueprintAssignable, Category="TrickyUserInterface")
	FOnButtonClickedSignature OnButtonClicked;
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category="ButtonWidget", meta=(BindWidget))
	TObjectPtr<UButton> Button_Main = nullptr;

private:
	UFUNCTION()
	void HandleButtonClick();
};
