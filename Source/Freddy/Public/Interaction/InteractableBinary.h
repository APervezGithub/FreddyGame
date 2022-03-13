// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractableBase.h"
#include "InteractableBinary.generated.h"

/**
 * Base class for interactable actors that can be interacted with to switch between two states
 * E.g. Door, Light Switch, Lock, Lever
 */
UCLASS()
class FREDDY_API AInteractableBinary : public AInteractableBase
{
	GENERATED_BODY()

public:
	/** Sets default values */
	AInteractableBinary();

	/** Toggles the actor */
	UFUNCTION(BlueprintCallable)
	void Toggle();

	/** Called when the toggled variable is replicated to clients */
	UFUNCTION()
	void OnRep_Toggled();

	/** Called when the toggled variable is replicated to clients, implemented in blueprints */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnRep_Toggled_BP();

	/** Sets properties to be replicated */
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

public:
	/** Whether the actor is in the toggled state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Toggled, Category = Interaction)
	bool Toggled;
};
