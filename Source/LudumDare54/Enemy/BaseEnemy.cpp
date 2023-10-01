// Made by Titled Goose Team during Ludum Dare 54l

#include "BaseEnemy.h"

#include "EnemyController.h"
#include "PickupBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "LudumDare54/Components/HitPointsComponent.h"
#include "LudumDare54/Components/WeaponManagerComponent.h"

AUBaseEnemy::AUBaseEnemy()
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

void AUBaseEnemy::Die()
{
	HitPointsComponent->OnValueZero.RemoveDynamic(this, &AUBaseEnemy::Die);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

float AUBaseEnemy::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	HitPointsComponent->DecreaseValue(DamageAmount);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AUBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	HitPointsComponent->OnValueZero.AddDynamic(this, &AUBaseEnemy::Die);
}

void AUBaseEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	HitPointsComponent->OnValueZero.RemoveDynamic(this, &AUBaseEnemy::Die);
	OnEnemyDied.Broadcast();
	Super::EndPlay(EndPlayReason);
}
