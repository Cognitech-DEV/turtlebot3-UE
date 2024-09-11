// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "XmlParser.h"
#include "ADrawMap.generated.h"

// #include <libxml/xmlmemory.hpp>
// #include <libxml/parser.hpp>

USTRUCT(BlueprintType)
struct TURTLEBOT3_API FLLNode {
    GENERATED_BODY()
    public:
        FVector Location;
        float Lat;
        float Lon;
};

USTRUCT(BlueprintType)
struct TURTLEBOT3_API FLLWay {
    GENERATED_BODY()
    public:
        TArray<FString> Nds;
        FString Type;
};
/**
 * 
 */
UCLASS()
class TURTLEBOT3_API AADrawMap : public AGeneratedDynamicMeshActor
{
	GENERATED_BODY()

    public:
        AADrawMap();

        UFUNCTION(BlueprintCallable, Category="CPPBlueprintFunctionLibrary")
            void ParseLanelet2();

        UFUNCTION(BlueprintCallable, Category="CPPBlueprintFunctionLibrary")
            void BuildMap();
	
        UPROPERTY(EditAnywhere)
            TMap<FString, FLLWay> _way_map;

        UPROPERTY(EditAnywhere)
            TMap<FString, FLLNode> _nd_map;
	
    private:
        static FTransform MakeTransform(const FVector &location, const FRotator &rotation, const FVector &scale); 
	
};

