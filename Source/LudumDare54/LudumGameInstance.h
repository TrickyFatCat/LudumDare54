// Made by Titled Goose Team during Ludum Dare 54 

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LudumGameInstance.generated.h"

constexpr int32 DefaultStageNumber = 0;

class UWorld;

/**
 * 
 */
UCLASS()
class LUDUMDARE54_API ULudumGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void IncreaseStageNumber();

	UFUNCTION(BlueprintCallable)
	void ResetStageNumber();

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 StageNumber = 0;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> Levels;

	UFUNCTION(BlueprintCallable)
	void OpenNextLevel(UObject* World);
};
