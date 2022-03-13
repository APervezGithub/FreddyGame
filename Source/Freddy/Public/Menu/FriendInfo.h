// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FriendInfo.generated.h"

/**
 * Hold information about an Epic friend
 */
UCLASS()
class FREDDY_API UFriendInfo : public UObject
{
	GENERATED_BODY()

public:
	/** Set default properties */
	UFriendInfo();

public:
	/** Index of friend in friends list */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Index;

	/** Unique Net ID of Friend */
	FUniqueNetIdWeakPtr UniqueId;

	/** Unique ID of friend, chopped for first half */
	FString UniqueIdStrChopped;

	/** Display name of the friend */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Whether the friend has sent an invite to you */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool PendingInvite;

	// Add variable for online status
	// Add variable for game/party status
};
