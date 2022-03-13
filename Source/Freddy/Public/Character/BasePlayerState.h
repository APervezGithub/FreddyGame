// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FREDDY_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	/** Sets default values */
	ABasePlayerState();

protected:
	/** Called when player state starts */
	virtual void BeginPlay() override;
};
