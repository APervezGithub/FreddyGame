// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

/**
 * Base class for controller
 */
UCLASS()
class FREDDY_API ABaseController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Sets default values */
	ABaseController();

	/** Called to bind functionality to input */
	virtual void SetupInputComponent() override;

	/** Called when controller possesses a pawn */
	virtual void OnPossess(APawn* InPawn) override;

	/** Called on client to initialize interaction executor */
	UFUNCTION(Client, Reliable)
	void InitializeExecutor();

	/** Called via input to turn at a given rate */
	void TurnAtRate(float Rate);

	/** Called via input to turn look up/down at a given rate */
	void LookUpAtRate(float Rate);

	/** Spawns a new character and possesses  it */
	UFUNCTION(Server, Reliable, WithValidation)
	void PossessNewCharacter(ABaseCharacter* NewCharacter);

protected:
	/** Called when the primary interact key is pressed */
	void PrimaryInteract();

	/** Called when the primary interact key is pressed */
	void SecondaryInteract();

protected:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	class UInteractionExecutor* InteractionExecutorRef;

	/** Whether the interaction executor has been intialized */
	bool ExecutorInitialized;
};
