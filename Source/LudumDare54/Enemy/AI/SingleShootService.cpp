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
	const auto Player = Cast<APawn>(Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName));

	if (Blackboard && Player && Controller)
	{
		if (const auto Weapon = Controller->GetPawn()->FindComponentByClass<UWeaponManagerComponent>())
		{
			Weapon->SetWeaponTargetPoint(WeaponId, Player->GetActorLocation());
			Weapon->MakeShot(WeaponId);
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
