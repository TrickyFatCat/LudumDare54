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
	const auto Player = Cast<APawn>(Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName));

	if (Controller) {
		if (const auto Weapon = Controller->GetPawn()->FindComponentByClass<UWeaponManagerComponent>())
		{
			Weapon->SetWeaponTargetPoint(WeaponId,Player ? Player->GetActorLocation() : FVector::Zero());
			Player ? Weapon->StartShooting(WeaponId) : Weapon->StopShooting(WeaponId); 
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
