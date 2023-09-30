// Made by Titled Goose Team during Ludum Dare 54 

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LudumGameInstance.generated.h"


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
	int32 StageNumber = 1;

	constexpr int32 DefaultStageNumber = 1;
};
