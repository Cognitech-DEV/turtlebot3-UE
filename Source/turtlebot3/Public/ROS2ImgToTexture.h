// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Msgs/ROS2Img.h"

#include "Engine/Texture2D.h"

#include "ROS2ImgToTexture.generated.h"

/**
 * 
 */
UCLASS()
class TURTLEBOT3_API UROS2ImgToTexture : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
    public:
        UFUNCTION(BlueprintCallable, Category="CPPBlueprintFunctionLibrary")
            static UTexture2D* Convert(FROSImg InMsg);
	
    private:
        static TArray<FColor> BGR2GBRA(const TArray<uint8> &gbr_img);
        static TArray<uint8> BGR2GBRAUint8(const TArray<uint8> &gbr_img);
	
	
};
