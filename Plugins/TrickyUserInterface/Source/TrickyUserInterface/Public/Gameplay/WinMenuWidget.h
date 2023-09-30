// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "WinMenuWidget.generated.h"

class UButtonWidget;
class UTransitionScreenWidget;

/**
 * A widget for creation of a simple win menu.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API UWinMenuWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category="WinMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Continue = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="WinMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Restart = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="WinMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Quit = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="WinMenu")
	TObjectPtr<UButtonWidget> ClickedButton = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="WinMenu", meta=(BindWidget))
	TObjectPtr<UTransitionScreenWidget> Widget_TransitionScreen = nullptr;

	/**Called when any button clicked.*/
	UFUNCTION(BlueprintNativeEvent, Category="WinMenu")
	void OnButtonClicked(UButtonWidget* Button);

	virtual void OnButtonClicked_Implementation(UButtonWidget* Button);

	/**
	 *Called when Button_Continue is clicked.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="WinMenu")
	void Continue();

	virtual void Continue_Implementation();

	/**
	 *Reloads current level. 
	 *Called when the transition screen were showed after click on Button_Restart.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="WinMenu")
	void Restart();

	virtual void Restart_Implementation();

	/**
	 *Quits the game.
	 *Called when the transition screen were showed after click on Button_Quit.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="WinMenu")
	void Quit();

	virtual void Quit_Implementation();

	/**
	 *Called when the transition screen finishes its show animation.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="WinMenu")
	void HandleTransitionShowed();

	virtual void HandleTransitionShowed_Implementation();
};
