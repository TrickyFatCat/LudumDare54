// Made by Titled Goose Team during Ludum Dare 54


#include "StopShoot.h"

#include "AIController.h"
#include "LudumDare54/Components/WeaponManagerComponent.h"

UStopShoot::UStopShoot()
{
}

EBTNodeResult::Type UStopShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller == nullptr) return EBTNodeResult::Failed;

	const auto Weapon = Controller->GetPawn()->FindComponentByClass<UWeaponManagerComponent>();
	if (Weapon == nullptr) return EBTNodeResult::Failed;

	Weapon->StopShooting(WeaponId);

	return EBTNodeResult::Succeeded;
}
