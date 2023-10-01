// Made by Titled Goose Team during Ludum Dare 54


#include "SingleShootService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare54/Components/WeaponManagerComponent.h"

USingleShootService::USingleShootService()
{
	NodeName = "Make single shoot";
}

void USingleShootService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (
		const auto HasAim = Blackboard && Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
		HasAim && Controller
	)
	{
		const auto Weapon = Controller->GetPawn()->FindComponentByClass<UWeaponManagerComponent>();
		if (Weapon) Weapon->MakeShot(WeaponId);
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
