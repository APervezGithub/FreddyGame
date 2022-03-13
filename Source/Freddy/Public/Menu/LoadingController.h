// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoadingController.generated.h"

/**
 * Player controller in the loading screen
 */
UCLASS()
class FREDDY_API ALoadingController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Sets loading to show logged in */
	UFUNCTION(BlueprintImplementableEvent)
	void SetLoggedIn();

	/** Sets loading to show session created */
	UFUNCTION(BlueprintImplementableEvent)
	void SetSessionCreated();

	/** Opens the main menu screen */
	UFUNCTION(BlueprintImplementableEvent)
	void OpenMainMenu();
};
