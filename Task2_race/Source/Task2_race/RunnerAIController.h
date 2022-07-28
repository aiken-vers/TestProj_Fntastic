// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MovingPawn.h"
#include "RunnerAIController.generated.h"


UCLASS()
class TASK2_RACE_API ARunnerAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	void Move();
	void Stay();
	void Return();	
	
protected:
	enum EState
	{
		Moving,
		Waiting,
		Returning
	};
private:
	FVector Destination;
	FTimerHandle MovingTimer;
	EState CurrentState = Moving;
	UPROPERTY()
	AMovingPawn* MovingPawn;
};
