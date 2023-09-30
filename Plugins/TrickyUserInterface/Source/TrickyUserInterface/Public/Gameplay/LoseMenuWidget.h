// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "LoseMenuWidget.generated.h"

class UButtonWidget;
class UTransitionScreenWidget;

/**
 * A widget for creation of a simple lose menu.
 */
UCLASS()
class TRICKYUSERINTERFACE_API ULoseMenuWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category="LoseMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Restart = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="LoseMenu", meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Quit = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="LoseMenu")
	TObjectPtr<UButtonWidget> ClickedButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="LoseMenu", meta=(BindWidget))
	TObjectPtr<UTransitionScreenWidget> Widget_TransitionScreen = nullptr;

	/**Called when any button clicked.*/
	UFUNCTION(BlueprintNativeEvent, Category="LoseMenu")
	void OnButtonClicked(UButtonWidget* Button);

	virtual void OnButtonClicked_Implementation(UButtonWidget* Button);

	/**
	 *Reloads current level. 
	 *Called when the transition screen were showed after click on Button_Restart.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="LoseMenu")
	void Restart();

	virtual void Restart_Implementation();

	/**
	 *Quits the game.
	 *Called when the transition screen were showed after click on Button_Quit.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="LoseMenu")
	void Quit();

	virtual void Quit_Implementation();

	/**
	 *Called when the transition screen finishes its show animation.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="LoseMenu")
	void HandleTransitionShowed();

	virtual void HandleTransitionShowed_Implementation();
};
