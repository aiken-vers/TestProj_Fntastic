// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Finish.h"
#include "Components/TextRenderComponent.h"
#include "PushButton.generated.h"



UCLASS()
class TASK2_RACE_API APushButton : public AFinish
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UTextRenderComponent* ButtonText;

	APushButton();

public:
	
};
