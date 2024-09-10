// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "ADrawMap.generated.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/**
 * 
 */
UCLASS()
class TURTLEBOT3_API AADrawMap : public AGeneratedDynamicMeshActor
{
	GENERATED_BODY()

    public:
        UFUNCTION(BlueprintCallable, Category="CPPBlueprintFunctionLibrary")
            static void ParseLanelet2();
	
    private:

	
	
	
};
