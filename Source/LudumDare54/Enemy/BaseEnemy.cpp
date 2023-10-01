// Made by Titled Goose Team during Ludum Dare 54l

#include "BaseEnemy.h"

#include "EnemyController.h"
#include "PickupBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "LudumDare54/Components/HitPointsComponent.h"
#include "LudumDare54/Components/WeaponManagerComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::Spawned;
	AIControllerClass = AEnemyController::StaticClass();

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
	WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>("WeaponManager");

	if (GetCharacterMovement())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void ABaseEnemy::Die()
{
	OnEnemyDied.Broadcast();
	HitPointsComponent->OnValueZero.RemoveDynamic(this, &ABaseEnemy::Die);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayAnimMontage(DeathMontage);
	SpawnPickup();
}

void ABaseEnemy::SpawnPickup() const
{
	if (PickupClass || FMath::RandRange(0, 100) >= DropChance) return;

	GetWorld()->SpawnActor<APickupBase>(
		PickupClass,
		GetMesh()->GetComponentLocation(),
		GetActorRotation(),
		FActorSpawnParameters()
	);
}

float ABaseEnemy::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	HitPointsComponent->DecreaseValue(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	HitPointsComponent->OnValueZero.AddDynamic(this, &ABaseEnemy::Die);
}

void ABaseEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	HitPointsComponent->OnValueZero.RemoveDynamic(this, &ABaseEnemy::Die);
	Super::EndPlay(EndPlayReason);
}
