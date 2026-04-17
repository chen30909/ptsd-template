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
    if (m_Stage == 1 && m_Stage_Object[i]->GetBlockType() == BROWN_OBJECT) {
        stage_goal_counter[1]--;
    }
}

int StageObject::GetPoint() {
    return stage_point_counter[m_Stage];
}
