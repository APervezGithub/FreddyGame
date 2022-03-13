// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UINotification.generated.h"

/**
 * Base class for UI notifications
 */
UCLASS(BlueprintType, Blueprintable)
class FREDDY_API UUINotification : public UObject
{
	GENERATED_BODY()
	
public:
	UUINotification();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NotificationText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NotificationDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Queued;
};
