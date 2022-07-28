// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerAIController.h"



void ARunnerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	MovingPawn = Cast<AMovingPawn>(InPawn);
	
	if(!MovingPawn)
		return;

	Destination = MovingPawn->Endpoint->GetActorLocation();
}

void ARunnerAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!MovingPawn)
		return;

	if(Destination.IsZero())
		return;

	if(2500 < FVector::DistSquared2D(Destination, MovingPawn->GetActorLocation()))
	{
		if(CurrentState==Moving)
		{
			if(!GetWorld()->GetTimerManager().TimerExists(MovingTimer))
				GetWorld()->GetTimerManager().SetTimer(MovingTimer, this, &ARunnerAIController::Stay,
					MovingPawn->MoveTimer, false);
			MovingPawn->MoveForward(1.0);
			MovingPawn->MovingSound(true);
		}
		if(CurrentState==Waiting)
		{			
			if(!GetWorld()->GetTimerManager().TimerExists(MovingTimer))
				GetWorld()->GetTimerManager().SetTimer(MovingTimer, this, &ARunnerAIController::Return,
					MovingPawn->StayTimer, false);
			MovingPawn->MoveForward(0);
			MovingPawn->MovingSound(false);
		}
		if(CurrentState==Returning)
		{
			if(!GetWorld()->GetTimerManager().TimerExists(MovingTimer))
				GetWorld()->GetTimerManager().SetTimer(MovingTimer, this, &ARunnerAIController::Move,
					MovingPawn->ReturnTimer, false);
			MovingPawn->MoveForward(-1);
			MovingPawn->MovingSound(true);
		}
	}
	else
	{
		MovingPawn->Escape();
		return;
	}

	auto TargetRotation = UKismetMathLibrary::FindLookAtRotation(MovingPawn->GetActorLocation(), Destination);
	TargetRotation.Pitch=0;
	TargetRotation.Roll=0;
	auto Rotation = GetControlRotation();
	Rotation.Pitch=0;
	Rotation.Roll=0;
	auto Direction = FRotator::NormalizeAxis(TargetRotation.Yaw - Rotation.Yaw);
	
	if(!TargetRotation.Equals(Rotation, 10))
	{
		if(!TargetRotation.Equals(Rotation, 90))
		{
			MovingPawn->MoveForward(0);
		}
		MovingPawn->RotateRight(Direction > 0 ? 1 : -1);
	}
	else
	{
		MovingPawn->RotateRight(0);
	}
	
}

void ARunnerAIController::Move()
{
	CurrentState = Moving;
	MovingPawn->TextMove();
}

void ARunnerAIController::Stay()
{
	if(MovingPawn->StayTimer>0)
	{
		CurrentState = Waiting;
		MovingPawn->TextStay();
	}		
	else if(MovingPawn->ReturnTimer>0)
	{
		CurrentState = Returning;
		MovingPawn->TextReturn();
	}
				
}

void ARunnerAIController::Return()
{
	if(MovingPawn->ReturnTimer>0)
	{
		CurrentState = Returning;
		MovingPawn->TextReturn();
	}		
	else
	{
		CurrentState = Moving;
		MovingPawn->TextMove();
	}		
}
