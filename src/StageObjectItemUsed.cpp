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

void StageObject::UseHammer( std::shared_ptr<Item> Tool ) {

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage_Object.at(i)->IfClick() ) {
            printf( "HAMMER\n");
            m_Stage_Object.at(i)->SetAppearBool(false);
            CheckAppearance( 1 , m_Stage , false );
            Tool->Update();
            Tool->SetImage( HAMMER_IMAGE );
        }
    }

}

void StageObject::UseMagicStick (std::shared_ptr<Item> Tool) {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( m_Stage_Object.at(i)->IfClick() ) {
            // cout<<"UseMagicStick"<<endl;
            std::random_device rd;  // 硬體隨機數產生器
            std::mt19937 gen(rd()); // Mersenne Twister 亂數引擎
            std::uniform_int_distribution<int> dist(5, 7); // 產生 5 到 7 之間的整數

            int random_number = dist(gen);

            m_Stage_Object.at(i)->SetCurrentType(random_number);
            m_Stage_Object.at(i)->SetBlockType(random_number);
            CheckSpecialObject(static_cast<int>(i));
            m_Stage_Object.at(i)->SetBlockType(NORMAL_OBJECT);
            
            m_Stage_Object[i]->SetGenerate(true);
            MakeDisappear();
            Tool->Update();
            Tool->SetImage(MAGIC_STICK_IMAGE);
            break;
        }
    }

}

void StageObject::UseMagicGlove(std::shared_ptr<Item> Tool) {

    auto objectArray = this->GetStageObject();
    
    if ( !objectArray.at(0)->GetVisibility() ) {
        is_click = 0;
    }
    for (int i = 1; i < m_Size + 1; ++i) {
        if (objectArray.at(i)->IfClick()) {
            if (objectArray.at(i)->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ||
                objectArray.at(i)->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT)
                continue;

            if (is_click == 0) {
                objectArray.at(0)->SetPosition(objectArray.at(i)->GetInformationPosition());
                objectArray.at(0)->SetVisible(true);
                is_click = i;
            } else {
                objectArray.at(0)->SetVisible(false);
                if (is_click == i) {
                    is_click = 0;
                    break;
                }
                int check = is_click;
                m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
                m_Stage_Object[check] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
                m_Stage_Object[i]->SetSwitched( MOVE_BY_TOOL );
                m_Stage_Object[check]->SetSwitched( MOVE_BY_TOOL );
                is_click = 0;
                CheckAppearance( 1 , m_Stage , false );
                Tool->Update();
                Tool->SetImage(GLOVES_IMAGE);
            }
        }
    }
}
