// Made by Titled Goose Team during Ludum Dare 54 


#include "LudumGameInstance.h"

#include "Kismet/GameplayStatics.h"

void ULudumGameInstance::IncreaseStageNumber()
{
	StageNumber++;
}

void ULudumGameInstance::ResetStageNumber()
{
	StageNumber = DefaultStageNumber;
}

void ULudumGameInstance::OpenNextLevel(UObject* World)
{
	if (Levels.Num() < 1)
	{
		return;
	}

	StageNumber += 1;;

	if (StageNumber >= Levels.Num())
	{
		StageNumber = 0;
	}
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(World, Levels[StageNumber]);
}
