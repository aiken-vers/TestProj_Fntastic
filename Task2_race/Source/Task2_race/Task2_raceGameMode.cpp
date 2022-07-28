// Copyright Epic Games, Inc. All Rights Reserved.

#include "Task2_raceGameMode.h"
#include "Task2_raceHUD.h"
#include "Task2_raceCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATask2_raceGameMode::ATask2_raceGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATask2_raceHUD::StaticClass();
}
