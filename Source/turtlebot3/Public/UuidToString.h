// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <Msgs/ROS2UUID.h>
#include "UuidToString.generated.h"

/**
 * 
 */
UCLASS()
class TURTLEBOT3_API UUuidToString : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
    
    public:
        UFUNCTION(BlueprintCallable, Category="CPPBlueprintFunctionLibrary")
        static FString Convert(const FROSUUID uuid);
    private:
	
	
	
};
