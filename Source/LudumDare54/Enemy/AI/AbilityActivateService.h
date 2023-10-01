// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AbilityActivateService.generated.h"


UCLASS()
class LUDUMDARE54_API UAbilityActivateService : public UBTService
{
	GENERATED_BODY()
public:
	UAbilityActivateService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
