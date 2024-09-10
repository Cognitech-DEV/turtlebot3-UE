// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.


#include "PredictedObject.h"


// Sets default values
APredictedObject::APredictedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // create root component
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = DefaultSceneRoot;

    // set mesh
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cube"));
    StaticMesh->SetStaticMesh(Mesh);

    // set material
    UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Game/Blueprints/AWUI/MPredictedObjectBB"));
    StaticMesh->SetMaterial(0, Material);

    // set static mesh to root component
    StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APredictedObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APredictedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

