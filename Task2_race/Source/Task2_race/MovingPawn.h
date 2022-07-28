
#pragma once

#include "CoreMinimal.h"
#include "Waypoint.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/RichTextBlock.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MovingPawn.generated.h"

class UStaticMeshComponent;

UCLASS()
class TASK2_RACE_API AMovingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Collision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UTextRenderComponent* SignMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UTextRenderComponent* SignReturning;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UAudioComponent* Audio_Moving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed=100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MovementAcceleration = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float RotationAcceleration = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float MoveTimer=1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float StayTimer=0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float ReturnTimer=0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	AWaypoint* Endpoint;
	
	AMovingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Scale);
	void RotateRight(float Scale);
	void Escape();
	void Death_Blink();
	void MovingSound(bool IsMoving);
	void TextMove();
	void TextStay();
	void TextReturn();

private:
	float ForwardScaleMax=0;
	float ForwardScaleCurrent=0;
	float RotateScaleMax=0;
	float RotateScaleCurrent=0;
	int Blinks = 2;
	bool Hidden = false;
	FTimerHandle DeathTimer;
};
