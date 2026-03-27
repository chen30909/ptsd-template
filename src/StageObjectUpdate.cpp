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

void StageObject::PointUpdate(int point ) {
    stage_point_counter[m_Stage] = point;
}

void StageObject::GoalUpdate( int i ) {
    switch ( m_Stage ) {
        case 1:
            if ( m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT ) {
                stage_goal_counter[1]--;
            }
            break;
        case 2:
            if ( m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT ) {
                stage_goal_counter[2]--;
            }
            break;
        case 3:
            stage_goal_counter[3] = stage_point_goal[3] - stage_point_counter[3];
            break;
        case 4:
            stage_goal_counter[4] = stage_point_goal[4] - stage_point_counter[4];
            break;
        case 5:
            if ( m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
                stage_goal_counter[5]--;
            }
            break;
        case 6:
            if ( m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT  && m_Stage_Object[i]->GetType() == NORMAL_OBJECT ) {
                stage_goal_counter[6]--;
            }
            break;
        case 7:
            if ( m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT  && m_Stage_Object[i]->GetType() == NORMAL_OBJECT ) {
                stage_goal_counter[7]--;
            }
            break;
        case 8:
            if ( m_Stage_Object[i]->GetCurrentType() == FLOWER_OBJECT || m_Stage_Object[i]->GetCurrentType() == TRIANGLEFLOWER_OBJECT || m_Stage_Object[i]->GetCurrentType() == STARFLOWER_OBJECT || m_Stage_Object[i]->GetCurrentType() == FLOWER_COMBINED_OBJECT || m_Stage_Object[i]->GetCurrentType() == FLOWER_STRIPE_OBJECT ) {
                stage_goal_counter[8]--;
            }
            break;
        case 9:
            if ( m_Stage_Object[i]->GetCurrentType() == STRIPE_OBJECT || m_Stage_Object[i]->GetCurrentType() == STRIPE_LEFT_RIGHT_OBJECT || m_Stage_Object[i]->GetCurrentType() == STRIPE_RIGHT_LEFT_OBJECT || m_Stage_Object[i]->GetCurrentType() == STRIPE_COMBINED_OBJECT || m_Stage_Object[i]->GetCurrentType() == FLOWER_STRIPE_OBJECT ) {
                stage_goal_counter[9]--;
            }
            break;
        case 10:
            if ( m_Stage_Object[i]->GetCurrentType() == STRIPE_OBJECT || m_Stage_Object[i]->GetCurrentType() == STRIPE_LEFT_RIGHT_OBJECT || m_Stage_Object[i]->GetCurrentType() == STRIPE_RIGHT_LEFT_OBJECT || m_Stage_Object[i]->GetCurrentType() == STRIPE_COMBINED_OBJECT || m_Stage_Object[i]->GetCurrentType() == FLOWER_STRIPE_OBJECT ) {
                stage_goal_counter[10]--;
            }
            break;
        case 11:
            if ( m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ) {
                stage_goal_counter[11]--;
            }
            break;
        case 12:
            if ( m_Stage_Object[i]->GetCurrentType() == RAINBOWBALL_OBJECT ) {
                stage_goal_counter[12]--;
            }
            
        default:
            break;
    }
}

int StageObject::GetPoint() {
    return stage_point_counter[m_Stage];
}
