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

void StageObject::ShuffleStageCharacter( int s ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 7);

    if (s != 1) {
        return;
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        if (m_Stage != 0) {
            auto type = obj->GetCurrentType();
            if (type != NORMAL_OBJECT && type != ONE_LAYER_COOKIE_OBJECT && type != TWO_LAYER_COOKIE_OBJECT) {
                continue;
            }
        }

        RandomChangeObject(i);

        obj->SetZIndex(10);
        obj->SetSize({20, 25});
        obj->DisAppear();
        obj->SetAppearBool(true);
        obj->SetBlockType(NORMAL_OBJECT);
        obj->SetCurrentType(NORMAL_OBJECT);

        obj->SetInformation(stage1[i]);
        obj->SetPosition(stage1_position[i]);
    }
}
