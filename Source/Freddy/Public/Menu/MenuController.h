// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

/**
 * Player controller in the main menu
 */
UCLASS()
class FREDDY_API AMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Updates the friends list */
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFriends();

protected:
	/** Called when controller is spawned */
	void BeginPlay();

public:
	FString ControllerName;
	/** Sets menu to show session created */
	//UFUNCTION(BlueprintImplementableEvent)
	//void AddNewSessionInvitation(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId, const FOnlineSessionSearchResult& InviteResult);
};
