// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CameraTracer.h"

#include "Camera/CameraComponent.h"
#include "Interaction/InteractableComponent.h"
#include "Interaction/InteractInterface.h"
#include "Kismet/GameplayStatics.h" 
#include "Kismet/KismetSystemLibrary.h"


UCameraTracer::UCameraTracer()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(false);
}

void UCameraTracer::Initialize(bool IsEnabled_, float InteractionDistance_, UCameraComponent* CameraRef_, EInteractorType TracerInteractorType_)
{
	SetIsReplicated(false);
	IsEnabled = IsEnabled_;
	PrimaryComponentTick.bCanEverTick = IsEnabled;
	InteractionDistance = InteractionDistance_;
	CameraRef = CameraRef_;
	TracerInteractorType = TracerInteractorType_;
}

void UCameraTracer::ComponentUpdated()
{
	UpdateInteractPrompt();
}

void UCameraTracer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsEnabled)
	{
		// Trace camera viewpoint
		FHitResult HitResult;
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true);
		bool bHit = CameraTrace(&HitResult, &RV_TraceParams);
		if (bHit)
		{
			RespondTrace(&HitResult);
		}
		else
		{
			RemoveFocused();
		}
	}
}

void UCameraTracer::BeginPlay()
{
	Super::BeginPlay();
}

void UCameraTracer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (FocusedActor)
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
		if (Interface)
		{
			Interface->EndFocus();
			Interface->GetComp()->RemoveObserver(this);
		}
		HideInteractPrompt();
	}
}

bool UCameraTracer::CameraTrace(FHitResult* HitResult, FCollisionQueryParams* RV_TraceParams)
{
	if (CameraRef == NULL) // Ensure controller and camera exists
	{
		return false;
	}
	// Find transformation of camera
	FVector CameraLoc = CameraRef->GetComponentLocation();
	FRotator CameraRot = CameraRef->GetComponentRotation();

	FVector Start = CameraLoc;
	FVector End = CameraLoc + (CameraRot.Vector() * InteractionDistance);

	TArray<AActor*> ActorsToIgnore;

	// Perform trace
	bool bHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Camera),
		false, ActorsToIgnore, EDrawDebugTrace::None, *HitResult, true, FLinearColor::Yellow, FLinearColor::White,
		1.0f);

	return bHit;
}

void UCameraTracer::RespondTrace(FHitResult* HitResult)
{
	// Find actor that was hit
	AActor* Interactable = HitResult->GetActor();
	if (Interactable)
	{
		// Change the focused actor
		if (Interactable != FocusedActor)
		{
			RemoveFocused();
			TrySetFocused(Interactable);
		}
	}
}

void UCameraTracer::TrySetFocused(AActor* NewFocused)
{
	// Get interface from actor
	IInteractInterface* Interface = Cast<IInteractInterface>(NewFocused);
	TScriptInterface<IInteractInterface> TInterface;
	TInterface.SetInterface(Interface);
	TInterface.SetObject(NewFocused);
	if (Interface) // Show focus on interactable objects
	{
		Interface->StartFocus();
		Interface->GetComp()->AddObserver(this);
		ShowInteractPrompt(TInterface, Interface->GetComp());
	}
	FocusedActor = NewFocused;
}

void UCameraTracer::RemoveFocused()
{
	if (FocusedActor)
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
		if (Interface)
		{
			Interface->EndFocus();
			Interface->GetComp()->RemoveObserver(this);
		}
		HideInteractPrompt();
		FocusedActor = nullptr;
	}
}
