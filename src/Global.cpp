#include "Global.hpp"
#include "App.hpp"


GamePhase currentPhase = PHASE_NORMAL;
std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

int is_click = 0;

int item_num[3] = {
    6, 6, 6
};

glm::vec2 item_position[3] {
    { -47 , -257.5 },
    { 0.5 , -257.5 },
    { 48  , -257.5 } 
};

glm::vec2 item_num_position[3] {
    { -34 , -238.5 },
    { 13.5 , -238.5 },
    { 61  , -238.5 } 
};

std::string LevelStageList[13] = {
    "",
    LEVEL_ONE_IMAGE,
    LEVEL_TWO_IMAGE,
    LEVEL_THREE_IMAGE,
    LEVEL_FOUR_IMAGE,
    LEVEL_FIVE_IMAGE,
    LEVEL_SIX_IMAGE,
    LEVEL_SEVEN_IMAGE,
    LEVEL_EIGHT_IMAGE,
    LEVEL_NINE_IMAGE,
    LEVEL_TEN_IMAGE
};

std::string ClearStageList[13] = {
    "",
    LEVEL_ONE_CLEAR,
    LEVEL_TWO_CLEAR,
    LEVEL_THREE_CLEAR,
    LEVEL_FOUR_CLEAR,
    LEVEL_FIVE_CLEAR,
    LEVEL_SIX_CLEAR,
    LEVEL_SEVEN_CLEAR,
    LEVEL_EIGHT_CLEAR,
    LEVEL_NINE_CLEAR,
    LEVEL_TEN_CLEAR
};

std::string CurrentStageList[13] = {
    "",
    LEVEL_ONE_CURRENT,
    LEVEL_TWO_CURRENT,
    LEVEL_THREE_CURRENT,
    LEVEL_FOUR_CURRENT,
    LEVEL_FIVE_CURRENT,
    LEVEL_SIX_CURRENT,
    LEVEL_SEVEN_CURRENT,
    LEVEL_EIGHT_CURRENT,
    LEVEL_NINE_CURRENT,
    LEVEL_TEN_CURRENT
};

glm::vec2 stage_position[13] = {
    {-100000, -100000},
    {-64.5, 87.5f},
    {0, 87.5f},
    {64.5, 87.5f},
    {64.5, 37.5f},
    {0, 37.5f},
    {-64.5, 37.5f},
    {-64.5, -17.5f},
    {0, -17.5f},
    {64.5, -17.5f},
    {64.5, -67.5f}
};

glm::vec2 stage_goal_position[13] = {
    {-100000, -100000},
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 },
    { -100 , 225 }
};

glm::vec2 point_position[13] = {
    {-100000, -100000},
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 },
    { 5 , 185 }
};

int stage_point_goal[13] = {
    0, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int stage_goal_counter[13] = {
    0, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

char stage_goal_type[13][30] = {
    "",
    "Remove Brown Object",
    "Map is empty",
    "Map is empty",
    "Map is empty",
    "Map is empty",
    "Map is empty",
    "Map is empty",
    "Map is empty",
    "Map is empty",
    "Map is empty"
};

int stage_point_counter[13] = {0};

int stage_moves[13] = {
    0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

bool ifClear[13] = {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true
};


glm::vec2 stage1_position[38] = {
    { -100000 , -100000 },
    { -87 , -70.5 }, { -87, -37.5 }, { -87, -4.5 } , { -87, 28.5 },
    { -57, -85.5 },  { -57, -52.5 },  { -57, -19.5 }, { -57, 13.5 }, { -57, 46.5 },
    { -27, -103.5 },{ -27, -67.5 }, { -27, -34.5 }, { -27, -1.5 }, { -27, 28.5 }, { -27, 61.5 },
    { 0, -118.5 }, { 0, -84.5 }, { 0, -52.5 }, { 0, -19.5 }, { 0, 13.5 }, { 0, 46.5 }, { 0, 79.5 },
    { 30, -103.5 }, { 30, -70.5 }, { 30, -37.5 }, { 30, -4.5 }, { 30, 31.5 }, { 30, 61.5 },
    { 57, -82.5 }, { 57, -49.5 }, { 57, -16.5 }, { 57, 13.5 }, { 57, 47.5 },
    { 87, -70.5 }, { 87, -37.5 }, { 87, -1.5 }, { 87, 31.5 }
};


int stage1_neibor[38][6] = { //clockwise
    { -1 , -1 , -1 , -1 , -1 , -1 },
    { 2 , 6 , 5 , -1 , -1 , -1 }, //1
    { 3 , 7 , 6 , 1 , -1 , -1 },
    { 4 , 8 , 7 , 2 , -1 , -1 },
    { -1 , 9 , 8 , 3 , -1 , -1 },//4
    { 6 , 11 , 10 , -1 , -1 , 1 },//5
    { 7 , 12 , 11 , 5 , 1 , 2 },
    { 8 , 13 , 12 , 6 , 2 , 3 },
    { 9 , 14 , 13 , 7 , 3 , 4 },
    { -1 , 15 , 14 , 8 , 4 , -1 },//9
    { 11 , 17 , 16 , -1 , -1 , 5 },//10
    { 12 , 18 , 17 , 10 , 5 , 6 },
    { 13 , 19 , 18 , 11 , 6 , 7 },
    { 14 , 20 , 19 , 12 , 7 , 8 },
    { 15 , 21 , 20 , 13 , 8 , 9 },
    { -1 , 22 , 21 , 14 , 9 , -1 },//15
    { 17 , 23 , -1 , -1 , -1 , 10 },//16
    { 18 , 24 , 23 , 16 , 10 , 11 },
    { 19 , 25 , 24 , 17 , 11 , 12 },
    { 20 , 26 , 25 , 18 , 12 , 13 },
    { 21 , 27 , 26 , 19 , 13 , 14 },
    { 22 , 28 , 27 , 20 , 14 , 15 },
    { -1 , -1 , 28 , 21 , 15 , -1 },//22
    { 24 , 29 , -1 , -1 , 16 , 17 },//23
    { 25 , 30 , 29 , 23 , 17 , 18 },
    { 26 , 31 , 30 , 24 , 18 , 19 },
    { 27 , 32 , 31 , 25 , 19 , 20 },
    { 28 , 33 , 32 , 26 , 20 , 21 },
    { -1 , -1 , 33 , 27 , 21 , 22 },//28
    { 30 , 34 , -1 , -1 , 23 , 24 },//29
    { 31 , 35 , 34 , 29 , 24 , 25 },
    { 32 , 36 , 35 , 30 , 25 , 26 },
    { 33 , 37 , 36 , 31 , 26 , 27 },
    { -1 , -1 , 37 , 32 , 27 , 28 },//33
    { 35 , -1 , -1 , -1 , 29 , 30 },//34
    { 36 , -1 , -1 , 34 , 30 , 31 },
    { 37 , -1 , -1 , 35 , 31 , 32 },
    { -1 , -1 , -1 , 36 , 32 , 33 }//37
};

Objectinformation stage1[38];
void InitializeStage1() {
    for ( int i = 0 ; i < 38 ; ++i ) {
        stage1[i].SetNeibor( stage1_neibor[i] );
        stage1[i].SetPosNumber( i );
        stage1[i].SetPosition( stage1_position[i] );
        stage1[i].SetStage(1);
    }
}


void InitializeStages() {
    InitializeStage1();
}
