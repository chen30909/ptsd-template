#include "StageObject.hpp"
#include "App.hpp"
#include "Global.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>
#include <vector>
#include <chrono>

namespace {
void ConfigureObstacleTile(
    const std::shared_ptr<GameCharacter>& obj,
    int currentType,
    const std::string& imagePath,
    int blockType,
    int stage,
    int index
) {
    obj->SetImage(imagePath);
    obj->SetBlock(NO_COLOR);
    auto& info = const_cast<Objectinformation&>(GetStageObjectInfo(stage, index));
    obj->SetInformation(info);
    obj->SetPosition(GetStageObjectPosition(stage, index));
    obj->SetZIndex(10);
    obj->SetSize({20, 25});
    obj->DisAppear();
    obj->SetAppearBool(true);
    obj->SetBlockType(blockType);
    obj->SetCurrentType(currentType);
}
}

void StageObject::SetUp(int stage) {
    for (auto& obj : m_Stage_Object) {
        if (obj && obj->GetAppearBool()) {
            obj->Appear();
        }
    }
    m_Stage_Object.at(0)->DisAppear();
    this->GetStageGoalObject()->Appear();
    InitializeStageCharacter(stage);
    CheckAppearance(0, stage, true);
}

void StageObject::InitializeStageCharacter(int s) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 7);

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        if (m_Stage != 0) {
            auto type = obj->GetCurrentType();
            if (type != NORMAL_OBJECT && type != ONE_LAYER_COOKIE_OBJECT && type != TWO_LAYER_COOKIE_OBJECT) {
                continue;
            }
        }

        if (IsOneLayerObstacleTile(s, static_cast<int>(i))) {
            ConfigureObstacleTile(obj, ONE_LAYER_COOKIE_OBJECT, COOKIE_ONE_IMAGE, NORMAL_OBJECT, s, static_cast<int>(i));
            continue;
        }
        if (IsTwoLayerObstacleTile(s, static_cast<int>(i))) {
            ConfigureObstacleTile(obj, TWO_LAYER_COOKIE_OBJECT, COOKIE_TWO_IMAGE, ONE_LAYER_COOKIE_OBJECT, s, static_cast<int>(i));
            continue;
        }
        RandomChangeObject(i);
        

        obj->SetZIndex(10);
        obj->SetSize({20, 25});
        obj->DisAppear();
        obj->SetAppearBool(true);
        obj->SetBlockType(NORMAL_OBJECT);
        obj->SetCurrentType(NORMAL_OBJECT);

        auto& info = const_cast<Objectinformation&>(GetStageObjectInfo(s, static_cast<int>(i)));
        obj->SetInformation(info);
        obj->SetPosition(GetStageObjectPosition(s, static_cast<int>(i)));
    }
}
