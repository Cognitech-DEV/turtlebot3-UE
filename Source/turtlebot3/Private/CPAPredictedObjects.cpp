// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.


#include "CPAPredictedObjects.h"

#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ACPAPredictedObjects::ACPAPredictedObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Node = CreateDefaultSubobject<UROS2NodeComponent>(TEXT("ROS2NodeComponent"));
    // these parameters can be change from BP
    Node->Name = TEXT("predicted_object_node");
    Node->Namespace = TEXT("cpp");

}

// Called when the game starts or when spawned
void ACPAPredictedObjects::BeginPlay()
{
	Super::BeginPlay();
	Node->Init();

    ROS2_CREATE_SUBSCRIBER(Node, this, TopicName, UROS2PredictedObjectsMsg::StaticClass(), &ACPAPredictedObjects::PredictedObjectsCb);
}
	
// Called every frame
void ACPAPredictedObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
   

void ACPAPredictedObjects::PredictedObjectsCb(const UROS2GenericMsg *in_msg) {
    const UROS2PredictedObjectsMsg *predicted_objects = Cast<UROS2PredictedObjectsMsg>(in_msg);
    FROSPredictedObjects msg;
    predicted_objects->GetMsg(msg);
    for (const auto &obj : msg.Objects) {
        FString uuid;
        for (const uint8 &i : obj.ObjectId.Uuid) {
            uuid.AppendChar(i);
        }

        UKismetSystemLibrary::PrintString(this, uuid, true, true, FColor::Blue, 2.f, TEXT("None"));
        
//         if (ObjectList.Contains(uuid)) {
//             FTransform *transform = MakeTransform(
//                obj.Kinematics.InitialPoseWithCovariance.Pose.Position, 
//                obj.Kinematics.InitiaoPoseWithCovariance.Pose.Orientation.rorator(),
//                FVector(1.0, 1.0, 1.0)
//                );
//            ObjectList[uuid].SetActorTransform(
//                transform,
//                false,
//                NULL,
//                ETeleportType::TeleportPhysics
//                );
//        } else {
//            FTransform *transform = MakeTransform(
//                obj.Kinematics.InitialPoseWithCovariance.Pose.Position, 
//                obj.Kinematics.InitiaoPoseWithCovariance.Pose.Orientation.rorator(),
//                FVector(1.0, 1.0, 1.0)
//                );
//            FActorSpawnParameters spawn_info;
//            PredictedObject* spawned_actor = GetWorld()->SpawnActor(
//                    PredictedObject::StaticClass(),
//                    transform,
//                    spawn_info
//                    );
//
//

//    }
    }
}
