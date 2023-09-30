// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrickyAnimationComponent.generated.h"


UCLASS(ClassGroup=(TrickyAnimationComponents), meta=(BlueprintSpawnableComponent))
class TRICKYANIMATIONCOMPONENTS_API UTrickyAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTrickyAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TrickyAnimationComponent")
	void PlayFromStart();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TrickyAnimationComponent")
	void PlayFromEnd();

	UFUNCTION(BlueprintCallable, Category="TrickyAnimations|TrickyAnimationComponent")
	void Reverse();
};
