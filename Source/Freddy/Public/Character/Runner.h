// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Runner.generated.h"

/**
 * Base class for runner character
 */

UCLASS()
class FREDDY_API ARunner : public ABaseCharacter
{
	GENERATED_BODY()

public:
	/** Sets default values */
	ARunner();

	/** Called on server when interacted with */
	virtual void OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType) override;

	/** Called after successful interaction on all players */
	virtual void MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType) override;

	/** Called after successful interaction on all players */
	virtual void ReactToInteract_Implementation(EInteractionType InteractionType, EInteractorType InteractorType) override;

protected:
	/** Called after player is haunted */
	void BecomeHaunted();

public:
	/** Flashlight component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Flashlight)
	class USpotLightComponent* FlashlightComponent;
};
