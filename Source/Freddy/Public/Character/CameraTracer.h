// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraTracer.generated.h"

/**
 * Traces viewport
 */

enum class EInteractorType : uint8;

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FREDDY_API UCameraTracer : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values */
	UCameraTracer();

	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Sets tracing values */
	UFUNCTION(BlueprintCallable)
	void Initialize(bool IsEnabled_, float InteractionDistance_, class UCameraComponent* CameraRef_, EInteractorType TracerInteractorType_);

	/** Called when the component is updated */
	void ComponentUpdated();

protected:
	/** Called when component is spawned */
	virtual void BeginPlay() override;

	/** Called when component is spawned */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * Traces from camera and returns if it hits anything
	 * @param HitResult  Pointer to the result of the trace, modified
	 * @param RV_TraceParams  Pointer to the parameters for the trace, not modified
	*/
	bool CameraTrace(FHitResult* HitResult, FCollisionQueryParams* RV_TraceParams);

	/** Responds to completed trace	*/
	void RespondTrace(FHitResult* HitResult);

	/** Sets the focused actor */
	void TrySetFocused(AActor* NewFocused);

	/** Removes the focused actor */
	void RemoveFocused();

	/** Shows the interaction prompt based on the interface and component */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowInteractPrompt(const TScriptInterface<class IInteractInterface>& Interface, class UInteractableComponent* Component);

	/** Updates the interaction prompt */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateInteractPrompt();

	/** Hides the interaction prompt */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HideInteractPrompt();

public:	
	/** First person camera of parent class */
	class UCameraComponent* CameraRef;

	/** Whether tracing is enabled */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsEnabled;

	/** Actor that the player is currently looking at */
	AActor* FocusedActor;

	/** Maximum distance that player can interact from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractionDistance;
	
protected:
	/** Type of interactor of tracer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInteractorType TracerInteractorType;
};
