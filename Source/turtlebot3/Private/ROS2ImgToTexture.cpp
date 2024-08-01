// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.


#include "ROS2ImgToTexture.h"


UTexture2D* UROS2ImgToTexture::Convert(FROSImg InMsg) {
    UTexture2D* texture;
    texture = UTexture2D::CreateTransient(InMsg.Width, InMsg.Height, PF_B8G8R8A8);

    if (!texture) {
        return nullptr;
    }

#if WITH_EDITORONLY_DATA
    texture->MipGenSettings = TMGS_NoMipmaps;
#endif

    texture->NeverStream = true;
    texture->SRGB = 0;


    // TArray<FColor> gbra_img = BGR2GBRA(InMsg.Data);
    // TArray<uint8> gbra_img = BGR2GBRAUint8(InMsg.Data);
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    FTexture2DMipMap& Mip = texture->GetPlatformData()->Mips[0];

    // void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
    FColor* Data = static_cast<FColor *>(Mip.BulkData.Lock(LOCK_READ_WRITE));

    for (int32 i = 0; i < InMsg.Data.Num();) {
        Data[int(i/3)] = FColor(InMsg.Data[i], InMsg.Data[i+1], InMsg.Data[i+2], 255);
        i += 3;
    }

    // FMemory::Memcpy(Data, &gbra_img, InMsg.Width * InMsg.Height * sizeof(uint8) * 4);
    // UE_LOG(LogTemp, Log, TEXT("Step is %d, size is %d, width is %d, height is %d"), InMsg.Step, InMsg.Data.Num(), InMsg.Width, InMsg.Height);
    Mip.BulkData.Unlock();
    // Mip = gbra_img;
    texture->UpdateResource();

    end = std::chrono::system_clock::now();
    double time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() / 1000.0);
    UE_LOG(LogTemp, Log, TEXT("calc time %lf [ms]"), time);
    UKismetSystemLibrary::PrintString(nullptr, FString::Printf(TEXT("calc time %lf [ms]"), time), true, true, FColor::Red, 2.f, TEXT("None"));
    return texture;
}

TArray<FColor> UROS2ImgToTexture::BGR2GBRA(const TArray<uint8> &gbr_img) {
    TArray<FColor> out_img; 
    out_img.Reserve(int(gbr_img.Num() / 3));
    for (int i=0; i<gbr_img.Num();) {
        out_img.Add(FColor(gbr_img[i], gbr_img[i+1], gbr_img[i+2], 255));
        i += 3;
    }
    return out_img;
}


TArray<uint8> UROS2ImgToTexture::BGR2GBRAUint8(const TArray<uint8> &gbr_img) {
    TArray<uint8> out_img; 
    out_img.Reserve(int(gbr_img.Num() * 4 / 3));
    for (int i=0; i<gbr_img.Num();) {
        out_img.Add(gbr_img[i]);
        out_img.Add(gbr_img[i+1]);
        out_img.Add(gbr_img[i+2]);
        out_img.Add(255);
        i += 3;
    }
    return out_img;
}


        
