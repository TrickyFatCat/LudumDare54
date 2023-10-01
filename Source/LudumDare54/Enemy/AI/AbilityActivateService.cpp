// Made by Titled Goose Team during Ludum Dare 54


#include "AbilityActivateService.h"

#include "AIController.h"
#include "LudumDare54/Enemy/AbilityComponent.h"

class UWeaponManagerComponent;

UAbilityActivateService::UAbilityActivateService()
{
	NodeName = "Activate Ability";
}

void UAbilityActivateService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard && Controller)
	{
		if (const auto Ability = Controller->GetPawn()->FindComponentByClass<UAbilityComponent>())
		{
			Ability->ActivateAbility();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
