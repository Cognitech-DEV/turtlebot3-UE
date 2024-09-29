// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ROS2Subscriber.h"
#include <Msgs/ROS2PredictedObjects.h>

#include "CPAPredictedObjects.generated.h"


UCLASS()
class TURTLEBOT3_API ACPAPredictedObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPAPredictedObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void PredictedObjectsCb(const UROS2GenericMsg *in_msg);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UROS2NodeComponent* Node = NULL;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TopicName = TEXT("/perception/object_recognition/objects");

    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // TMap<int, PredictedObject> ObjectList; 
	
};
