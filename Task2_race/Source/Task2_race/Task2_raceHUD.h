// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Task2_raceHUD.generated.h"

UCLASS()
class ATask2_raceHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATask2_raceHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

