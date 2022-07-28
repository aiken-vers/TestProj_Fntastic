// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryActor.h"

#include "PushButton.h"


// Sets default values
AFactoryActor::AFactoryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
	Building = CreateDefaultSubobject<UStaticMeshComponent>("Building");
	Building->SetupAttachment(RootComponent);
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(Building);
	Audio_Spawn = CreateDefaultSubobject<UAudioComponent>("Audio_Spawn");
	Audio_Spawn->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFactoryActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AFactoryActor::SpawnRunnerTick, 1.0f, true);
}

void AFactoryActor::SpawnRunnerTick()
{
	if(!SpawnRunner || !Endpoint || !FactoryButton)
		return;

	if(!FactoryButton->IsActive)
		return;

	if(!bReadyToSpawn)
		return;
	
	auto Transform = SpawnPoint->GetComponentTransform();
	auto Runner = GetWorld()->SpawnActorDeferred<AMovingPawn>(SpawnRunner, Transform,
		nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Runner->Endpoint = Endpoint;
	Runner->MoveTimer = RunnerMove;
	Runner->StayTimer = RunnerStay;
	Runner->ReturnTimer = RunnerReturn;	
		
	UGameplayStatics::FinishSpawningActor(Runner, Transform);
		
	if(Audio_Spawn)
		Audio_Spawn->Play();

	bReadyToSpawn = false;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &AFactoryActor::OnCooldown, SpawnRate, false);
}

void AFactoryActor::OnCooldown()
{
	bReadyToSpawn = true;
}


