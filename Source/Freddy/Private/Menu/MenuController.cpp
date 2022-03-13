// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuController.h"

#include "Game/EOSGameInstance.h"


void AMenuController::BeginPlay()
{
	Super::BeginPlay();
	UEOSGameInstance* EOSGameInstance = Cast<UEOSGameInstance>(GetGameInstance());
	if (EOSGameInstance)
	{
		EOSGameInstance->SetMenuController(this);
	}
}