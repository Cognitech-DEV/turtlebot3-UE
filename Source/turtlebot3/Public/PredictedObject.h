// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PredictedObject.generated.h"

UCLASS()
class TURTLEBOT3_API APredictedObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APredictedObject();

    // Component which has transform information
    UPROPERTY(EditAnywhere)
    TObjectPtr<USceneComponent> DefaultSceneRoot;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UStaticMeshComponent> StaticMesh;

    UPROPERTY(EditAnywhere)
    FString id;

    UPROPERTY(EditAnywhere)
    float decay_time;

    UPROPERTY(EditAnywhere)
    float likelihood;

    UPROPERTY(EditAnywhere)
    bool is_request;

    UPROPERTY(EditAnywhere)
    FVector size;
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
