// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notification/UINotification.h"
#include "InviteNotification.generated.h"

/**
 * Notification for session invitation
 */
UCLASS()
class FREDDY_API UInviteNotification : public UUINotification
{
	GENERATED_BODY()
	
public:
	/** Set default properties */
	UInviteNotification();

	/** Name of the user who sent the invitation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString InviterName;

	/** Unique ID that the invite is from */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString FromIdStr;
};
