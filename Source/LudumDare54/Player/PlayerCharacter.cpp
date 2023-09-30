// Made by Titled Goose Team during Ludum Dare 54


#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TrickyGameModeLibrary.h"
#include "LudumDare54/Components/HitPointsComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
}

void APlayerCharacter::BeginPlay()
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);

		//Using Ability
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacter::UseAbility);

		//Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::Pause);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
}

void APlayerCharacter::Shoot()
{
	UE_LOG(LogTemp, Error, TEXT("PEW PEW PEW"));
}

void APlayerCharacter::UseAbility()
{
	UE_LOG(LogTemp, Error, TEXT("I used an ability"));
}

void APlayerCharacter::Pause()
{
	UTrickyGameModeLibrary::TogglePause(this);
}
