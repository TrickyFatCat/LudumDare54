// Made by Titled Goose Team during Ludum Dare 54


#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "LudumDare54/Components/HitPointsComponent.h"
#include "LudumDare54/Components/WeaponManagerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "LudumDare54/Components/DashComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh());

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
	WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>("WeaponManager");

	DashComponent = CreateDefaultSubobject<UDashComponent>("DashComponent");
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
	WeaponMesh->SetLeaderPoseComponent(GetMesh());
	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::HandleAnyDamage);
	HitPointsComponent->OnValueZero.AddDynamic(this, &APlayerCharacter::HandleDeath);
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HitPointsComponent->GetValue() > 0)
	{
		AimAtCursor();
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerCharacter::StartShooting);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this,
		                                   &APlayerCharacter::StopShooting);


		//Using Ability
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Started, this,
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

	UpdateWeaponTargetPoint(0);
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

void APlayerCharacter::UpdateWeaponTargetPoint(const int32 WeaponId)
{
	const FVector SocketLocation = GetMesh()->GetSocketLocation("WeaponSocket");
	FVector TargetPoint = FVector(ProjectionLocation.X, ProjectionLocation.Y, SocketLocation.Z);
	const FVector UnitVec = UKismetMathLibrary::GetDirectionUnitVector(SocketLocation, TargetPoint);
	const FVector FwdVec = GetActorForwardVector();
	const float DotProduct = UKismetMathLibrary::Dot_VectorVector(FwdVec.GetSafeNormal(),
	                                                              FVector(UnitVec.X, UnitVec.Y, 0.f).GetSafeNormal());
	const float Angle = UKismetMathLibrary::DegAcos(DotProduct);
	TargetPoint = Angle < AimAngleThreshold ? TargetPoint : FwdVec + FwdVec * 5000.f;
	WeaponManagerComponent->SetWeaponTargetPoint(WeaponId, TargetPoint);
}

void APlayerCharacter::StartShooting()
{
	WeaponManagerComponent->StartShooting(0);
}

void APlayerCharacter::StopShooting()
{
	WeaponManagerComponent->StopShooting(0);
}

void APlayerCharacter::UseAbility()
{
		FVector Direction = GetActorForwardVector();
	
    	if (GetVelocity().GetSafeNormal() != FVector::ZeroVector)
    	{
    		Direction.X = GetVelocity().GetSafeNormal().X;
    		Direction.Y = GetVelocity().GetSafeNormal().Y;
    		Direction.Z = 0.f;
    	}
    
    	DashComponent->Dash(Direction);
}

void APlayerCharacter::Pause()
{
	UTrickyGameModeLibrary::TogglePause(this);
}

void APlayerCharacter::HandleAnyDamage(AActor* DamagedActor,
                                       float Damage,
                                       const UDamageType* DamageType,
                                       AController* InstigatedBy,
                                       AActor* DamageCauser)
{
	HitPointsComponent->DecreaseValue(Damage);
}

void APlayerCharacter::HandleDeath()
{
	ATrickyGameModeBase* GameMode = UTrickyGameModeLibrary::GetTrickyGameMode(this);

	if (GameMode)
	{
		GameMode->FinishSession(false);
	}

	GetMovementComponent()->StopMovementImmediately();
	WeaponManagerComponent->StopShooting(0);
}