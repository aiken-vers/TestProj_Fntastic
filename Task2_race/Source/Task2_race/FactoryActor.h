// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPawn.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "FactoryActor.generated.h"

class UArrowComponent;
class UStaticMeshComponent;
class UBoxComponent;
class APushButton;

UCLASS()
class TASK2_RACE_API AFactoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Collision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Building;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* SpawnPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UAudioComponent* Audio_Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TSubclassOf<AMovingPawn> SpawnRunner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float SpawnRate = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RunnerMove=1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RunnerStay=0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RunnerReturn=0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	AWaypoint* Endpoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	APushButton* FactoryButton;
	
	AFactoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnRunnerTick();
	void OnCooldown();

public:	
	// Called every frame
	bool bReadyToSpawn = true;

private:
	FTimerHandle SpawnTimer;
	FTimerHandle CooldownTimer;
};
