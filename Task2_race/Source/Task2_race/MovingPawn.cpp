
#include "MovingPawn.h"

#include "EditorTutorial.h"

AMovingPawn::AMovingPawn()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
	
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(RootComponent);
	
	SignMoving = CreateDefaultSubobject<UTextRenderComponent>("SignMoving");
	SignMoving->SetupAttachment(RootComponent);	
	SignReturning = CreateDefaultSubobject<UTextRenderComponent>("SignReturning");
	SignReturning->SetupAttachment(RootComponent);
	
	Audio_Moving = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	Audio_Moving->SetupAttachment(RootComponent);

	
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPawn::BeginPlay()
{
	Super::BeginPlay();	
}

void AMovingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForwardScaleCurrent = FMath::Lerp(ForwardScaleCurrent, ForwardScaleMax, MovementAcceleration);	
	auto Location = GetActorLocation();
	auto ForwardVector =  GetActorForwardVector();
	SetActorLocation(Location+ForwardVector *ForwardScaleCurrent*MovementSpeed*DeltaTime, false);
	//SetActorLocation(Location+ForwardVector *MovementSpeed*DeltaTime, false);
	auto Rotation = GetActorRotation();
	Rotation.Yaw = (Rotation.Yaw + RotationSpeed * RotateScaleCurrent * DeltaTime);
	SetActorRotation(Rotation);
}


void AMovingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovingPawn::MoveForward(float Scale)
{
	ForwardScaleMax = Scale;
}

void AMovingPawn::RotateRight(float Scale)
{
	RotateScaleMax = Scale;	
}

void AMovingPawn::Escape()
{
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AMovingPawn::Death_Blink, 0.5f, true);	
}

void AMovingPawn::Death_Blink()
{
	if(Hidden)
	{
		Hidden = false;
		Blinks-=1;
	}
	else
	{
		Hidden = true;
	}
	SetActorHiddenInGame(Hidden);
	
	if(Blinks<0)
	{
		GetWorld()->GetTimerManager().ClearTimer(DeathTimer);
		Destroy();
	}
}

void AMovingPawn::MovingSound(bool IsMoving)
{
	if(!Audio_Moving)
		return;
	if(!IsMoving)
		Audio_Moving->Stop();
	
	if(IsMoving && !Audio_Moving->IsPlaying())
		Audio_Moving->Play();
}

void AMovingPawn::TextMove()
{
	SignMoving->SetVisibility(true);
	SignReturning->SetVisibility(false);
}

void AMovingPawn::TextStay()
{
	SignMoving->SetVisibility(false);
	SignReturning->SetVisibility(false);
}

void AMovingPawn::TextReturn()
{
	SignMoving->SetVisibility(false);
	SignReturning->SetVisibility(true);
}

