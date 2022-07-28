#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/AudioComponent.h"
#include "Finish.generated.h"

UCLASS()
class TASK2_RACE_API AFinish : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UBoxComponent* Trigger;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* Body;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    USpotLightComponent* InactiveLight;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    USpotLightComponent* ActiveLight;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
    bool IsActive = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UAudioComponent* Audio_Finish;
	AFinish();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
    void OnTargetBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);    
    UFUNCTION()
    void OnTargetEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    virtual void OnConstruction(const FTransform& Transform) override;	

public:		
	void Activate(bool active);
	
	
};
