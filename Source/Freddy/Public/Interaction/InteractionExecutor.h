// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionExecutor.generated.h"

enum class EInteractorType : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FREDDY_API UInteractionExecutor : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values */
	UInteractionExecutor();

	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/** Sets interaction values */
	UFUNCTION(BlueprintCallable)
	void Initialize(class UCameraTracer* CameraTracer_, AActor* CharacterRef_, enum EInteractorType ExecutorInteractorType_);

	/** Called when player interacts */
	void InteractPressed(enum EInteractionType InteractionType);

	/** Called to show client effects of interaction */
	void InteractLocal(enum EInteractionType InteractionType);

	/** Called on server to confirm and complete server interaction */
	UFUNCTION(Server, Reliable, WithValidation)
	void InteractServer(enum EInteractionType InteractionType, AActor* FocusedActor);

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

public:
	/** Camera tracer */
	class UCameraTracer* CameraTracer;

	/** Type of interactor of executor */
	EInteractorType ExecutorInteractorType;

	/** Interacting actor */
	AActor* CharacterRef;
};
