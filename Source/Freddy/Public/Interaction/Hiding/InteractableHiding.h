// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "InteractableHiding.generated.h"

/**
 * Base class for actors that you can hide in
 */
UCLASS()
class FREDDY_API AInteractableHiding : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	/** Sets default values */
	AInteractableHiding();

	/** Called on server when interacted with */
	virtual void OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType) override;

protected:
	/** Called on server when interacted with */
	FVector GetAbsoluteHidingLocation();

protected:
	/** Relative location that character will be at to hide */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HidingLocation;
};
