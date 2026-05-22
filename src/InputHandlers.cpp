#include "App.hpp"
#include "Global.hpp"
#include "StageConfig.hpp"

#include <thread>
#include <limits>

#include "Util/Keycode.hpp"

namespace {
int g_drag_start_index = 0;
glm::vec2 g_drag_start_cursor = {0.0f, 0.0f};

bool CursorHitsObject(const std::shared_ptr<GameCharacter>& obj) {
    if (!obj || !obj->GetVisibility()) return false;

    const glm::vec2 mousePos = Util::Input::GetCursorPosition();
    const glm::vec2 pos = obj->GetPosition();
    const glm::vec2 size = obj->GetSize();

    const bool insideX = (mousePos.x >= pos.x - size.x / 2.0f && mousePos.x <= pos.x + size.x / 2.0f);
    const bool insideY = (mousePos.y >= pos.y - size.y / 2.0f && mousePos.y <= pos.y + size.y / 2.0f);
    return insideX && insideY;
}

int FindSwipeTarget(const std::vector<std::shared_ptr<GameCharacter>>& objectArray, int sourceIndex, const glm::vec2& dragVector, int boardSize) {
    if (sourceIndex <= 0 || sourceIndex >= static_cast<int>(objectArray.size())) return 0;
    if (glm::length(dragVector) < 10.0f) return 0;

    const auto& source = objectArray.at(sourceIndex);
    const glm::vec2 sourcePos = source->GetInformationPosition();

    float bestScore = -std::numeric_limits<float>::infinity();
    int bestNeighbor = 0;

    for (int side = 0; side < 6; ++side) {
        const int rawNeighbor = source->GetInformationNeibor()[side];
        const int neighborIndex = rawNeighbor % (boardSize + 1);
        if (rawNeighbor == -1 || neighborIndex <= 0 || neighborIndex > boardSize) {
            continue;
        }

        const auto& neighbor = objectArray.at(neighborIndex);
        if (!neighbor) continue;
        if (neighbor->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ||
            neighbor->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT) {
            continue;
        }

        glm::vec2 neighborVector = neighbor->GetInformationPosition() - sourcePos;
        const float score = glm::dot(glm::normalize(dragVector), glm::normalize(neighborVector));
        if (score > bestScore) {
            bestScore = score;
            bestNeighbor = neighborIndex;
        }
    }

    return bestScore > 0.5f ? bestNeighbor : 0;
}
}

bool PhaseInitialImage(std::shared_ptr<Character>& chara_obj) {
    if (chara_obj->GetVisibility()) {
        if (chara_obj->IfClick()) {
            chara_obj->SetVisible(false);
            return true;
        }
    }
    return false;
}

int PhaseHomePage(const std::vector<std::shared_ptr<Character>>& buttoms) {
    for (int i = 1; i <= GetPlayableStageCount(); ++i)
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
        g_drag_start_index = 0;
        return false;
    }

    if (StageObject->HasActiveAnimations()) {
        objectArray.at(0)->SetVisible(false);
        g_drag_start_index = 0;
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
            g_drag_start_index = 0;
            objectArray.at(0)->SetVisible(false);
            return false;
        }
    }

    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        g_drag_start_index = 0;
        for (int i = 1; i < size + 1; ++i) {
            if (!CursorHitsObject(objectArray.at(i))) {
                continue;
            }
            if (objectArray.at(i)->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ||
                objectArray.at(i)->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT) {
                break;
            }

            g_drag_start_index = i;
            g_drag_start_cursor = Util::Input::GetCursorPosition();
            objectArray.at(0)->SetPosition(objectArray.at(i)->GetInformationPosition());
            objectArray.at(0)->SetVisible(true);
            break;
        }
    }

    if (g_drag_start_index != 0 && Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        const glm::vec2 dragVector = Util::Input::GetCursorPosition() - g_drag_start_cursor;
        if (glm::length(dragVector) > 18.0f) {
            const int target = FindSwipeTarget(objectArray, g_drag_start_index, dragVector, size);
            objectArray.at(0)->SetVisible(false);
            if (target != 0 && target != g_drag_start_index) {
                StageObject->CheckClickSwitch(g_drag_start_index, target, point);
            }
            g_drag_start_index = 0;
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        g_drag_start_index = 0;
        objectArray.at(0)->SetVisible(false);
    }

    return stage_goal_counter[stage] <= 0 && currentPhase == PHASE_NORMAL;
}

void DebugPhaseStage1(std::vector<std::shared_ptr<GameCharacter>>& objectArray) {
    DebugModeOfPosition(objectArray, 0);
    if (Util::Input::IsKeyUp(Util::Keycode::R)) {
        DebugModeCancel(objectArray, 0);
    }
}
