// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TrickyGameModeBase.h"
#include "TrickyHUDGame.generated.h"

class UBaseUserWidget;

/**
 * A base HUD class for gameplay. It automatically show and hide widgets depending on a game state.
 */
UCLASS(Abstract)
class TRICKYUSERINTERFACE_API ATrickyHUDGame : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/**A widget which will be shown in the Inactive game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> InactiveStateWidget = nullptr;
	
	/**A widget which will be shown in the Preparation game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> PreparationScreenWidget = nullptr;
	
	/**A widget which will be shown in the InProgress game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> GameplayScreenWidget = nullptr;
	
	/**A widget which will be shown in the Pause game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> PauseScreenWidget = nullptr;
	
	/**A widget which will be shown in the win game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> WinScreenWidget = nullptr;

	/**A widget which will be shown in the lose game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> LoseScreenWidget = nullptr;
	
	/**A widget which will be shown in the transition game state.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HUD")
	TSubclassOf<UBaseUserWidget> TransitionScreenWidget = nullptr;
private:
	UPROPERTY(BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess))
	TMap<EGameModeState, TObjectPtr<UBaseUserWidget>> UserWidgets;

	UPROPERTY(BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess))
	TObjectPtr<UBaseUserWidget> ActiveWidget = nullptr;

	UFUNCTION()
	void OnGameModeSessionChanged(EGameModeState NewState);
	
	void CreateUserWidget(const EGameModeState State, TSubclassOf<UBaseUserWidget> WidgetClass);
};
