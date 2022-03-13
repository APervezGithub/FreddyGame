// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Chaser.generated.h"

/**
 * Base class for chaser character
 */

UCLASS()
class FREDDY_API AChaser : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	/** Sets default values */
	AChaser();
};
