// Made by Titled Goose Team during Ludum Dare 54


#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TrickyGameModeLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "LudumDare54/Components/HitPointsComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
}

void APlayerCharacter::BeginPlay()
{
	PlayerController = Cast<APlayerController>(Controller);
	
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	PlayerController->SetControlRotation(FRotator(0.f, -45.f, 0.f));
	
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCursor();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

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

void APlayerCharacter::AimAtCursor()
{
	ProjectCursorToWorld();
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ProjectionLocation);
	SetActorRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));
}

void APlayerCharacter::ProjectCursorToWorld()
{
	if (!PlayerController)
	{
		ProjectionLocation = FVector::ZeroVector;
		return;
	}

	FVector WorldLocation, WorldDirection;

	if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		const bool bPointFound = CalculateProjection(WorldLocation,
		                                             WorldDirection,
		                                             1000.f,
		                                             GetActorLocation(),
		                                             FVector::UpVector,
		                                             ProjectionLocation);

		if (!bPointFound)
		{
			ProjectionLocation = FVector::ZeroVector;
		}
	}
	else
	{
		ProjectionLocation = FVector::ZeroVector;
	}
}

bool APlayerCharacter::CalculateProjection(const FVector& RayOrigin,
                                           const FVector& RayDirection,
                                           const float Range,
                                           const FVector& PlaneOrigin,
                                           const FVector& PlaneNormal,
                                           FVector& Intersection)
{
	const FVector Vec1 = FVector(((RayDirection * Range) + RayOrigin) - RayOrigin);
	const float Dot1 = FVector::DotProduct(PlaneOrigin - RayOrigin, PlaneNormal);
	const float Dot2 = FVector::DotProduct(Vec1, PlaneNormal);
	Intersection = FVector(RayOrigin + (Vec1 * (Dot1 / Dot2)));

	return Dot2 != 0.f;
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
