// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableComponent.h"

#include "Character/CameraTracer.h"
#include "Interaction/InteractInterface.h"
#include "Net/UnrealNetwork.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	PrimaryInteractable = true;
	SecondaryInteractable = true;
}

void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInteractableComponent::CanInteract(EInteractionType InteractionType)
{
	switch (InteractionType)
	{
		case EInteractionType::Primary:
		{
			return PrimaryInteractable;
			break;
		}
		case EInteractionType::Secondary:
		{
			return SecondaryInteractable;
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
}

void UInteractableComponent::SetCanInteract(EInteractionType InteractionType, bool NewInteractable)
{
	switch (InteractionType)
	{
		case EInteractionType::Primary:
		{
			PrimaryInteractable = NewInteractable;
			break;
		}
		case EInteractionType::Secondary:
		{
			SecondaryInteractable = NewInteractable;
			break;
		}
	}
	UpdateObservers();
}

void UInteractableComponent::AddObserver(UCameraTracer* CameraObserver)
{
	CameraObservers.AddUnique(CameraObserver);
}

void UInteractableComponent::RemoveObserver(UCameraTracer* CameraObserver)
{
	CameraObservers.RemoveSingle(CameraObserver);
}

void UInteractableComponent::UpdateObservers()
{
	for (auto CameraObserver : CameraObservers)
	{
		if (CameraObserver)
		{
			CameraObserver->ComponentUpdated();
		}
	}
}

void UInteractableComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(UInteractableComponent, PrimaryInteractable);
	DOREPLIFETIME(UInteractableComponent, SecondaryInteractable);
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}