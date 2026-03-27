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
using namespace std;

void StageObject::RandomChangeObject( int current_pos ) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 7);

    int ramdom_number = distrib(gen);

    switch ( ramdom_number )
    {
        case BLUE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/blueNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( BLUE_OBJECT );
            break;
        case BROWN_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/brownNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( BROWN_OBJECT );
            break;
        case GREEN_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/greenNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( GREEN_OBJECT );
            break;
        case PINK_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/pinkNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( PINK_OBJECT );
            break;
        case ORANGE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/orangeNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( ORANGE_OBJECT );
            break;
        case WHITE_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/whiteNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( WHITE_OBJECT );
            break;
        case YELLOW_OBJECT:
            m_Stage_Object[current_pos]->SetImage( GA_RESOURCE_DIR"/Image/GameObject/yellowNormal.png" );
            m_Stage_Object[current_pos]->SetBlock( YELLOW_OBJECT );
            break;
        default:
            break;
    }
}

bool StageObject::IsSameColor(int blockType1, int blockType2) {
    return ((blockType1 % 10) == (blockType2 % 10) 
    && blockType1 != NO_COLOR && blockType2 != NO_COLOR);
}
