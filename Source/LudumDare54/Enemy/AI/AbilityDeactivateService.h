// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AbilityDeactivateService.generated.h"


UCLASS()
class LUDUMDARE54_API UAbilityDeactivateService : public UBTService
{
	GENERATED_BODY()
public:
	UAbilityDeactivateService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
