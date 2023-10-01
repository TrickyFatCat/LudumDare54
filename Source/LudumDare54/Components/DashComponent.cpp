// Made by Titled Goose Team during Ludum Dare 54


#include "DashComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "LudumDare54/Player/PlayerCharacter.h"


UDashComponent::UDashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDashComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<APlayerCharacter>(GetOwner());

	if (Character)
	{
		MovementComponent = Character->FindComponentByClass<UCharacterMovementComponent>();
		PlayerController = Cast<APlayerController>(Character->GetController());
	}
}


void UDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDashComponent::Dash(const FVector& Direction)
{
	if (!MovementComponent && !Character && !PlayerController) return;

	if (IsOnCooldown()) return;

	Character->LaunchCharacter(Direction * DashPower, true, true);

	SetIsDashing(true);

	FTimerHandle DashTimerHandle;
	const FTimerDelegate DashTimerDelegate = FTimerDelegate::CreateUObject(this, &UDashComponent::SetIsDashing, false);
	GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, DashTimerDelegate, DashTime, false);

	GetWorld()->GetTimerManager().SetTimer(DashCooldownHandle, DashCooldown, false);

	OnDashActivated.Broadcast();
}

FTimerHandle UDashComponent::GetCooldownHandle() const
{
	return DashCooldownHandle;
}

bool UDashComponent::IsOnCooldown() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(DashCooldownHandle);
}

float UDashComponent::GetCooldownTime() const
{
	return DashCooldown;
}

bool UDashComponent::GetIsDashing()
{
	return bIsDashing;
}

void UDashComponent::SetIsDashing(const bool bEnableDash)
{
	if (bEnableDash == bIsDashing)
	{
		return;
	}

	bIsDashing = bEnableDash;
	if (bIsDashing)
	{
		Character->DisableInput(PlayerController);
	}
	else
	{
		Character->EnableInput(PlayerController);
		OnDashFinished.Broadcast();
	};
}
