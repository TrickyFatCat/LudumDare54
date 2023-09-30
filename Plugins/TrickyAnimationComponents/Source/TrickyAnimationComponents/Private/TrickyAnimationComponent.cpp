// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "TrickyAnimationComponent.h"


UTrickyAnimationComponent::UTrickyAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTrickyAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTrickyAnimationComponent::TickComponent(float DeltaTime,
                                              ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTrickyAnimationComponent::PlayFromStart()
{
}

void UTrickyAnimationComponent::PlayFromEnd()
{
}

void UTrickyAnimationComponent::Reverse()
{
}
