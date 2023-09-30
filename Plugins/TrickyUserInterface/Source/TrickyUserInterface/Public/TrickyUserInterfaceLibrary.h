// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyUserInterfaceLibrary.generated.h"

UENUM(BlueprintType)
enum class EFormatTime : uint8
{
	MM_SS_MsMs UMETA(DisplayName="MM:SS.MsMs"),
	MM_SS_Ms UMETA(DisplayName="MM:SS.Ms"),
	MM_SS UMETA(DisplayName="MM:SS"),
	SS_MsMs UMETA(DisplayName="SS.MsMs"),
	SS_Ms UMETA(DisplayName="SS.Ms"),
	SS UMETA(DisplayName="SS")
};

/**
 * A library which contain simple helper functions to adjust settings of the game and more
 */
UCLASS()
class TRICKYUSERINTERFACE_API UTrickyUserInterfaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**Sets quality level from low (0) to epic (3)*/
	UFUNCTION(BlueprintCallable, Category="TrickyUserInterface")
	static void SetQualitySettings(const int32 QualityIndex);

	/**Sets screen mode*/
	UFUNCTION(BlueprintCallable, Category="TrickyUserInterface")
	static void SetScreenMode(EWindowMode::Type ScreenMode);

	/**Sets resolution scale*/
	UFUNCTION(BlueprintCallable, Category="TrickyUserInterface")
	static void SetResolutionScale(const float Scale = 1.f);

	/**Sets screen resolution*/
	UFUNCTION(BlueprintCallable, Category="TrickyUserInterface")
	static void SetResolution(const int32 Width, const int32 Height);

	/**Converts given time in seconds to a chosen format*/
	UFUNCTION(BlueprintPure, Category="TrickyUserInterface")
	static FString ConvertTimeSeconds(const float TimeSeconds, const EFormatTime TimeFormat);
};
