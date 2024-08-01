// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.


#include "UuidToString.h"

FString UUuidToString::Convert(const FROSUUID uuid) {
    FString f_uuid;
    for (const uint8 &c : uuid.Uuid) {
        f_uuid.AppendChar(c);
    }
    return f_uuid;
}
