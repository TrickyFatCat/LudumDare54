// Made by Titled Goose Team during Ludum Dare 54l

#include "BaseEnemy.h"

#include "EnemyController.h"
#include "PickupBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "LudumDare54/Components/HitPointsComponent.h"

AUBaseEnemy::AUBaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::Spawned;
	AIControllerClass = AEnemyController::StaticClass();

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");

	if (GetCharacterMovement())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AUBaseEnemy::PlayDeathMontage()
{
	GetCapsuleComponent()->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetMesh()->SetCollisionResponseToChannels(ECR_Ignore);
	PlayAnimMontage(DeathMontage);
	SpawnPickup();
}

void AUBaseEnemy::SpawnPickup() const
{
	if (PickupClass || FMath::RandRange(0, 100) >= DropChance) return;

	GetWorld()->SpawnActor<APickupBase>(
		PickupClass,
		GetMesh()->GetComponentLocation(),
		GetActorRotation(),
		FActorSpawnParameters()
	);
}

void AUBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	HitPointsComponent->OnValueZero.AddDynamic(this, &AUBaseEnemy::PlayDeathMontage);
}

void AUBaseEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnEnemyDied.Broadcast();
	Super::EndPlay(EndPlayReason);
}
