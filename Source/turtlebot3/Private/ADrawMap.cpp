// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.


#include "ADrawMap.h"



void AADrawMap::ParseLanelet2() {
    std::string file_path = "/home/kuriatsu/Downloads/nishishinjuku_autoware_map/lanelet2_map.osm";

    xmlDocPtr doc = xmlParseFile(file_path);
    if (doc == NULL) {
        UE_LOG(LogTemp, Log, TEXT("empty doc"), time);

        xmlFreeDoc(doc);
        return;
    }

    xmlNodePtr cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        UE_LOG(LogTemp, Log, TEXT("doc wrong type"), time);
        xmlFreeDoc(doc);
        return;
    }

    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar*)
