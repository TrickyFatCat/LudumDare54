// Made by Titled Goose Team during Ludum Dare 54


#include "ShootService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare54/Components/WeaponManagerComponent.h"

UShootService::UShootService()
{
	NodeName = "Shooting";
}

void UShootService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	if (Controller) {
		const auto Weapon = Controller->GetPawn()->FindComponentByClass<UWeaponManagerComponent>();
		if (Weapon) HasAim ? Weapon->StartShooting(WeaponId) : Weapon->StopShooting(WeaponId);
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
