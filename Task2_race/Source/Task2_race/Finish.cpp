
#include "Finish.h"




AFinish::AFinish()
{ 	
	PrimaryActorTick.bCanEverTick = false;
	
	Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFinish::OnTargetBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AFinish::OnTargetEndOverlap);
	RootComponent = Trigger;
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(RootComponent);
	InactiveLight = CreateDefaultSubobject<USpotLightComponent>("InactiveLight");
	InactiveLight->SetupAttachment(RootComponent);
	ActiveLight = CreateDefaultSubobject<USpotLightComponent>("ActiveLight");
	ActiveLight->SetupAttachment(RootComponent);
	Audio_Finish = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	Audio_Finish->SetupAttachment(RootComponent);
}

void AFinish::BeginPlay()
{
	Super::BeginPlay();	
}

void AFinish::OnTargetBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Activate(true);
	
	if(Audio_Finish)
		Audio_Finish->Play();
}

void AFinish::OnTargetEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Activate(false);
}

void AFinish::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if(!IsActive)
    {
    	InactiveLight->SetVisibility(true);
    	ActiveLight->SetVisibility(false);
    }
    else
    {
    	InactiveLight->SetVisibility(false);
    	ActiveLight->SetVisibility(true);
    }
}

void AFinish::Activate(bool active)
{
	IsActive = active;
	InactiveLight->SetVisibility(!IsActive);
    ActiveLight->SetVisibility(IsActive);    
}


