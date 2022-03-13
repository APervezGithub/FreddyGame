// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InviteInfo.generated.h"

/**
 * Hold information about an invitation to session
 */
UCLASS()
class FREDDY_API UInviteInfo : public UObject
{
	GENERATED_BODY()

public:
	/** Set default properties */
	UInviteInfo();

public:
	/** Index of invite in invitations list */
	int Index;

	/** Unique ID that the invite is from */
	const FUniqueNetId* FromId;

	/** Unique ID that the invite is from, chopped for first half */
	FString FromIdStrChopped;

	/** Invited session */
	const FOnlineSessionSearchResult* InviteResult;
};
