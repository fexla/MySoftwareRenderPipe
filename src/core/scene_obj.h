//
// Created by q on 2023/10/26.
//

#ifndef MYSOFTWARERENDERPIPE_SCENE_OBJ_H
#define MYSOFTWARERENDERPIPE_SCENE_OBJ_H

#include "transform.h"
#include "materials/material.h"

struct scene_obj {
    std::string modelId;
    transform objTransform;
    const material *objMaterial;

    scene_obj(std::string modelId, const transform &objTransform) :
            modelId(std::move(modelId)), objTransform(objTransform), objMaterial(&DEFAULT_MATERIAL) {}

    scene_obj(std::string modelId, const transform &objTransform, material *objMaterial) :
            modelId(std::move(modelId)), objTransform(objTransform), objMaterial(objMaterial) {}
};

#endif //MYSOFTWARERENDERPIPE_SCENE_OBJ_H
