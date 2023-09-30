// Made by Titled Goose Team during Ludum Dare 54


#include "GameCamera.h"

#include "Camera/CameraComponent.h"


AGameCamera::AGameCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	UCameraComponent* CameraComp = GetCameraComponent();
	CameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComp->SetOrthoWidth(5250);
	CameraComp->SetAspectRatio(1.777778);
	CameraComp->SetRelativeRotation(FRotator(-45.0, -45.0, 0.0));
	CameraComp->SetRelativeLocation(FVector(-2380, 2380, 3250));	
}

