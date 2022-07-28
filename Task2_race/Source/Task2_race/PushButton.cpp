// Fill out your copyright notice in the Description page of Project Settings.


#include "PushButton.h"

APushButton::APushButton()
{
	ButtonText = CreateDefaultSubobject<UTextRenderComponent>("SignMoving");
	ButtonText->SetupAttachment(RootComponent);
}

