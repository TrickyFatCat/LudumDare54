// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButtonWidget;
class UTransitionScreenWidget;

/**
 * A widget for creation of a simple pause menu.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API UPauseMenuWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PauseMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Resume = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PauseMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Restart = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PauseMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Quit = nullptr;

	UPROPERTY()
	TObjectPtr<UButtonWidget> ClickedButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PauseMenu", meta=(BindWidget))
	UTransitionScreenWidget* Widget_TransitionScreen = nullptr;

	/**Called when one of the buttons is clicked.*/
	UFUNCTION(BlueprintNativeEvent, Category="PauseMenu")
	void OnButtonClick(UButtonWidget* Button);

	virtual void OnButtonClick_Implementation(UButtonWidget* Button);

	/**
	 *Reloads current level. 
	 *Called when the transition screen were showed after click on Button_Restart.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="PauseMenu")
	void Restart();

	virtual void Restart_Implementation();

	/**
	 *Quits the game. 
	 *Called when the transition screen were showed after click on Button_Quit.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="PauseMenu")
	void Quit();

	virtual void Quit_Implementation();

	/**Called when the transition screes finishes its show animation.*/
	UFUNCTION(BlueprintNativeEvent, Category="PauseMenu")
	void TransitionScreenShowed();

	virtual void TransitionScreenShowed_Implementation();
};
