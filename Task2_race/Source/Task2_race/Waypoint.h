#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS()
class TASK2_RACE_API AWaypoint : public AActor
{
	GENERATED_BODY()
	
public:		
	AWaypoint();

protected:
	
	virtual void BeginPlay() override;

public:			

};
