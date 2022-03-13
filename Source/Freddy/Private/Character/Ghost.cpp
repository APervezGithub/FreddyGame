// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Ghost.h"

AGhost::AGhost() :ABaseCharacter()
{
	// Set character interactor type
	CharacterInteractorType = EInteractorType::Ghost;
}