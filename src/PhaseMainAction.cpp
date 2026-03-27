#include "App.hpp"
#include "Global.hpp"

#include <thread>

#include "Util/Keycode.hpp"

bool PhaseInitialImage(std::shared_ptr<Character>& chara_obj) {
    if (chara_obj->GetVisibility()) {
        if (chara_obj->IfClick()) {
            std::cout << "Character clicked!" << std::endl;
            chara_obj->SetVisible(false);
            return true;
        }
    }
    return false;
}

int PhaseHomePage(const std::vector<std::shared_ptr<Character>>& buttoms) {
    for (int i = 1; i < 11; ++i)
        {
        if (buttoms.at(i)->IfClick() && ifClear[i - 1])
            return i;
    }
    return 0;
}

bool PhaseStage(std::shared_ptr<StageObject> StageObject, int size, std::shared_ptr<TaskText> point, int stage, std::vector<std::shared_ptr<Item>> Tools ) {
    auto objectArray = StageObject->GetStageObject();
    if ( currentPhase == PHASE_ITEM_USED ) {
        for ( int i = 0 ; i < 3 ; ++i ) {
            if ( Tools.at(i)->ifClickInUse() && Tools.at(i)->Click() ) {
                if ( i == 1 )
                    Tools.at(i)->SetImage( MAGIC_STICK_IMAGE );
                else if ( i == 2 )
                    Tools.at(i)->SetImage( GLOVES_IMAGE );
                else if ( i == 0 )
                    Tools.at(i)->SetImage( HAMMER_IMAGE );
                Tools.at(i)->UnClick();
                currentPhase = PHASE_NORMAL;
            }
        }   
        return false;
    }
    if ( currentPhase != PHASE_NORMAL ) {
        objectArray.at(0)->SetVisible(false);
        return false;
    }
    
    for ( int i = 0 ; i < 3 ; ++i ) {
        if ( Tools.at(i)->ifClickInUse() ) {
            if ( i == 1 ) {
                Tools.at(i)->SetImage( RESOURCE_DIR"/Image/GameObject/item2Click.png" );
            }
            else if ( i == 2 ) {
                Tools.at(i)->SetImage( RESOURCE_DIR"/Image/GameObject/item3Click.png" );
            }
            else if ( i == 0 ) {
                Tools.at(i)->SetImage( RESOURCE_DIR"/Image/GameObject/item1Click.png");
            }
            Tools.at(i)->SetClick();
            currentPhase = PHASE_ITEM_USED;
            return false;
        }
    }
    if ( !objectArray.at(0)->GetVisibility() ) {
        is_click = 0;
    }
    for (int i = 1; i < size + 1; ++i) {
        if (objectArray.at(i)->IfClick()) {
            if (objectArray.at(i)->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ||
                objectArray.at(i)->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT)
                continue;

            if (is_click == 0) {
                objectArray.at(0)->SetPosition(objectArray.at(i)->GetInformationPosition());
                objectArray.at(0)->SetVisible(true);
                is_click = i;
                // printf("Click on object %d\n", i);
            } else {
                objectArray.at(0)->SetVisible(false);
                if (is_click == i) {
                    is_click = 0;
                    break;
                }
                // printf("Click on object2 %d\n", i);
                int check = is_click;
                StageObject->CheckClickSwitch(check, i, point);
                is_click = 0;
            }
        }
    }
    return stage_goal_counter[stage] <= 0 && currentPhase == PHASE_NORMAL;
}

void DebugPhaseStage1(std::vector<std::shared_ptr<GameCharacter>>& objectArray) {
    DebugModeOfPosition(objectArray, 0);
    if (Util::Input::IsKeyUp(Util::Keycode::R)) {
        DebugModeCancel(objectArray, 0);
    }
}