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

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        if (m_Stage != 0) {
            auto type = obj->GetCurrentType();
            if (type != NORMAL_OBJECT && type != ONE_LAYER_COOKIE_OBJECT && type != TWO_LAYER_COOKIE_OBJECT) {
                continue;
            }
        }

        if (s == 5 && i < 27 && obj->GetCurrentType() != NORMAL_OBJECT ) {
            obj->SetImage(COOKIE_ONE_IMAGE);
            obj->SetBlock(NO_COLOR);
            obj->SetInformation(stage5[i]);
            obj->SetPosition(stage5_position[i]);
            obj->SetZIndex(10);
            obj->SetSize({20, 25});
            obj->DisAppear();
            obj->SetAppearBool(true);
            obj->SetBlockType(NORMAL_OBJECT);
            obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
            continue;
        } 
        if (s == 6 && m_Size - i < 35 && obj->GetCurrentType() != NORMAL_OBJECT) {
            if ( obj->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage6[i]);
                obj->SetPosition(stage6_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
            } 
            else if ( obj->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_TWO_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage6[i]);
                obj->SetPosition(stage6_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(ONE_LAYER_COOKIE_OBJECT);
                obj->SetCurrentType(TWO_LAYER_COOKIE_OBJECT);
            }
            continue;
        } 
        if ( s == 7 && obj->GetCurrentType() != NORMAL_OBJECT) {
            if ( one_layer_7.find(i) != one_layer_7.end() ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
                continue;
            }
            else if ( two_layer_7.find(i) != two_layer_7.end() && obj->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_TWO_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(ONE_LAYER_COOKIE_OBJECT);
                obj->SetCurrentType(TWO_LAYER_COOKIE_OBJECT);
                continue;
            }
            else if ( two_layer_7.find(i) != two_layer_7.end() && obj->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
                continue;
            }
        } 
        if ( s == 10 && obj->GetCurrentType() != NORMAL_OBJECT) {
            if ( one_layer_10.find(i) != one_layer_10.end() ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage10[i]);
                obj->SetPosition(stage10_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
                continue;
            }
        }
        /*if ( s == 11 && obj->GetCurrentType() != NORMAL_OBJECT) {
            if ( two_layer_11.find(i) != two_layer_11.end() && obj->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_TWO_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage11[i]);
                obj->SetPosition(stage11_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(ONE_LAYER_COOKIE_OBJECT);
                obj->SetCurrentType(TWO_LAYER_COOKIE_OBJECT);
                continue;
            }
            else if ( two_layer_11.find(i) != two_layer_11.end() && obj->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
                obj->SetImage(COOKIE_ONE_IMAGE);
                obj->SetBlock(NO_COLOR);
                obj->SetInformation(stage11[i]);
                obj->SetPosition(stage11_position[i]);
                obj->SetZIndex(10);
                obj->SetSize({20, 25});
                obj->DisAppear();
                obj->SetAppearBool(true);
                obj->SetBlockType(NORMAL_OBJECT);
                obj->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
                continue;
            }
        }*/
        RandomChangeObject(i);

        obj->SetZIndex(10);
        obj->SetSize({20, 25});
        obj->DisAppear();
        obj->SetAppearBool(true);
        obj->SetBlockType(NORMAL_OBJECT);
        obj->SetCurrentType(NORMAL_OBJECT);

        switch (s) {
            case 1:
                obj->SetInformation(stage1[i]);
                obj->SetPosition(stage1_position[i]);
                break;
            case 2:
                obj->SetInformation(stage2[i]);
                obj->SetPosition(stage2_position[i]);
                break;
            case 3:
                obj->SetInformation(stage3[i]);
                obj->SetPosition(stage3_position[i]);
                break;
            case 4:
                obj->SetInformation(stage4[i]);
                obj->SetPosition(stage4_position[i]);
                break;
            case 5:
                obj->SetInformation(stage5[i]);
                obj->SetPosition(stage5_position[i]);
                break;
            case 6:
                obj->SetInformation(stage6[i]);
                obj->SetPosition(stage6_position[i]);
                break;
            case 7:
                obj->SetInformation(stage7[i]);
                obj->SetPosition(stage7_position[i]);
                break;
            case 8:
                obj->SetInformation(stage8[i]);
                obj->SetPosition(stage8_position[i]);
                break;
            case 9:
                obj->SetInformation(stage9[i]);
                obj->SetPosition(stage9_position[i]);
                break;
            case 10:
                obj->SetInformation(stage10[i]);
                obj->SetPosition(stage10_position[i]);
                break;
            /*case 11:
                obj->SetInformation(stage11[i]);
                obj->SetPosition(stage11_position[i]);
                break;
            case 12:
                obj->SetInformation(stage12[i]);
                obj->SetPosition(stage12_position[i]);
                break;*/
            default:
                break;
        }
    }
}
