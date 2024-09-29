// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.


#include "ADrawMap.h"

AADrawMap::AADrawMap() {
    // BuildMap();
}

void AADrawMap::BeginPlay() {
    ParseLanelet2();
    BuildMap();
}

void AADrawMap::OnConstruction(const FTransform& Transform) {
    UDynamicMesh *DM = this->DynamicMeshComponent->GetDynamicMesh();
    DM->Reset();
    UE_LOG(LogTemp, Log, TEXT("[ADrawMap] building box")); // way
    FGeometryScriptPrimitiveOptions primitive_options;
    UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(
        DM,
        primitive_options,
        Transform,
        10.0,
        10.0,
        10.0,
        0,
        0,
        0
        );
    Super::OnConstruction(Transform);
}

FTransform AADrawMap::MakeTransform(const FVector &location, const FRotator &rotation, const FVector &scale) {
    return UKismetMathLibrary::MakeTransform(location, rotation, scale);
}

void AADrawMap::ParseLanelet2() {
    FString file_path = FString("/home/kuriatsu/Downloads/nishishinjuku_autoware_map/lanelet2_map.osm");
    FXmlFile file(file_path);
    if (!file.IsValid()) {
        UE_LOG(LogTemp, Log, TEXT("empty doc"), time);
        return;
    } 

    UE_LOG(LogTemp, Log, TEXT("load map"));
    FXmlNode* root = file.GetRootNode();
    // FXmlNode* way = root->FindChildNode("way");
    // UE_LOG(LogTemp, Log, TEXT("GetAttribute %s"), *(way->GetAttribute(FString("id")))); // 1
    // UE_LOG(LogTemp, Log, TEXT("GetContent %s"), *(way->GetContent())); // show none
    // UE_LOG(LogTemp, Log, TEXT("GetTag %s"), *(way->GetTag())); // way

    for (const auto& root_c : root->GetChildrenNodes()) {
        if (root_c->GetTag() == FString("way")) {
            FLLWay ll_way;
            for (const auto& root_cc : root_c->GetChildrenNodes()) {
                if (root_cc->GetTag() == FString("nd")) {
                    ll_way.Nds.Add(root_cc->GetAttribute(FString("ref")));
                } 
                else if (root_cc->GetTag() == FString("tag")) {
                    ll_way.Type = root_cc->GetAttribute(FString("v"));
                }
            }
            _way_map.Add(root_c->GetAttribute(FString("id")), ll_way);
        }
        else if (root_c->GetTag() == FString("node")) {
            FLLNode ll_node;
            ll_node.Lat = FCString::Atof(*root_c->GetAttribute(FString("lat")));
            ll_node.Lon = FCString::Atof(*root_c->GetAttribute(FString("lon")));
            float x=0.0, y=0.0, z=0.0;
            for (const auto& root_cc : root_c->GetChildrenNodes()) {
                if(root_cc->GetAttribute(FString("k")) == FString("local_x")) {
                    x = FCString::Atof(*root_cc->GetAttribute("v")) * 100.0;
                } 
                else if(root_cc->GetAttribute(FString("k")) == FString("local_y")) {
                    y = FCString::Atof(*root_cc->GetAttribute("v")) * -100.0;
                }
                else if(root_cc->GetAttribute(FString("k")) == FString("ele")) {
                    z = FCString::Atof(*root_cc->GetAttribute("v")) * 100.0;
                }
            }
            ll_node.Location = FVector(x, y, z);
            _nd_map.Add(root_c->GetAttribute(FString("id")), ll_node);
        }
    }
    
    UE_LOG(LogTemp, Log, TEXT("GetTag %d"), _nd_map.Num()); // way
    
}

void AADrawMap::BuildMap() {
    UDynamicMesh *DM = DynamicMeshComponent->GetDynamicMesh();
    DM->Reset();
    UE_LOG(LogTemp, Log, TEXT("Start building map")); // way
    TArray<FVector2D> vertices = {
        FVector2D(0.0, 0.0),
        FVector2D(10.0, 0.0),
        FVector2D(0.0, 0.0)
    };
    TArray<float> emp_array;
    FGeometryScriptPrimitiveOptions primitive_options;
    FTransform emp_transform;

    for (const auto &ll_way : _way_map) {

        TArray<FTransform> sweep_path;
        auto &Nds = ll_way.Value.Nds;

        for (int i=0; i<Nds.Num()-1; ++i) {
            FRotator rot = UKismetMathLibrary::MakeRotFromX(_nd_map[Nds[i+1]].Location - _nd_map[Nds[i]].Location); 
            FTransform transform = MakeTransform(_nd_map[Nds[i]].Location, rot, FVector(0,0,0));
            sweep_path.Add(transform);
        }

        FRotator rot = UKismetMathLibrary::MakeRotFromX(_nd_map[Nds[Nds.Num()-1]].Location - _nd_map[Nds[Nds.Num()-2]].Location); 
        FTransform transform = MakeTransform(_nd_map[Nds[Nds.Num()-1]].Location, rot, FVector(0,0,0));
        sweep_path.Add(transform);
        UE_LOG(LogTemp, Log, TEXT("xyz %f, %f, %f"), _nd_map[Nds[Nds.Num()-1]].Location[0], _nd_map[Nds[Nds.Num()-1]].Location[1], _nd_map[Nds[Nds.Num()-1]].Location[2]); // way
        UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendSweepPolyline(
            DM, 
            primitive_options, 
            emp_transform, 
            vertices, 
            sweep_path, 
            emp_array, 
            emp_array
        );


    }
    UE_LOG(LogTemp, Log, TEXT("Finish building map")); // way

}
