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

void StageObject::CheckClickSwitch( int check , int i , std::shared_ptr<TaskText> point ) {
    for ( int j = 0 ; j < 6 ; ++j ) {
        if( m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1) == check && m_Stage_Object[i]->GetInformationNeibor()[j] <= m_Size) {
            m_Stage_Object[i]->SetSwitched(2);
            m_Stage_Object[check]->SetSwitched(2);
            m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
            std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
            m_Stage_Object[check] = m_Stage_Object[i];
            m_Stage_Object[i] = NewObject;

            if ( m_Stage_Object[check]->GetCurrentType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[check]->SetBlock( m_Stage_Object[i]->GetBlockType() );
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[i]->GetCurrentType() );
            }
            if ( m_Stage_Object[i]->GetCurrentType() == RAINBOWBALL_OBJECT ) {
                m_Stage_Object[i]->SetBlock( m_Stage_Object[check]->GetBlockType() ); //color
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[check]->GetCurrentType() );
            }

            // flower + flower
            if ( m_Stage_Object[check]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[check]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT ) {
                m_Stage_Object[i]->SetCurrentType( FLOWER_COMBINED_OBJECT );
                m_Stage_Object[check]->SetCurrentType( FLOWER_COMBINED_OBJECT );
            }

            //to be opt.
            // flower + stripe 1
            if ( m_Stage_Object[check]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[check]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[i]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT  ) {
                m_Stage_Object[i]->SetBlockType( NORMAL_OBJECT);
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[check]->GetCurrentType());
                m_Stage_Object[check]->SetCurrentType( FLOWER_STRIPE_OBJECT );
                m_Stage_Object[i]->SetCurrentType( NORMAL_OBJECT );
            }

            //to be opt.
            // flower + stripe 2
            if ( m_Stage_Object[check]->GetCurrentType() >= FLOWER_OBJECT && m_Stage_Object[check]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[i]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT   ) {
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[i]->GetCurrentType());
                m_Stage_Object[check]->SetBlockType( NORMAL_OBJECT);
                m_Stage_Object[i]->SetCurrentType( FLOWER_STRIPE_OBJECT );
                m_Stage_Object[check]->SetCurrentType( NORMAL_OBJECT );
            }

            // stripe + stripe
            if ( m_Stage_Object[check]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[check]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT &&  m_Stage_Object[i]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[i]->GetCurrentType() <= STRIPE_RIGHT_LEFT_OBJECT   ) {
                m_Stage_Object[i]->SetBlockType( m_Stage_Object[i]->GetCurrentType());
                m_Stage_Object[check]->SetBlockType( m_Stage_Object[check]->GetCurrentType());
                m_Stage_Object[check]->SetCurrentType( STRIPE_COMBINED_OBJECT );
                m_Stage_Object[i]->SetCurrentType( STRIPE_COMBINED_OBJECT );
            }

            //all check but no disappear
            if ( !CheckAppearance( 1 , m_Stage , false ) ) {
                m_Stage_Object[i]->SwitchPosition( m_Stage_Object[check] );
                std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[check];
                m_Stage_Object[check] = m_Stage_Object[i];
                m_Stage_Object[i] = NewObject;
            } 
            else {
                point->SetMove( point->GetMove() - 1 );
            }
            point->SetPoint( stage_point_counter[m_Stage] );
            point->UpdateText();
            break;
        }
    }
}

bool StageObject::CheckAppearance(int s, int now_stage, bool ifShuffle) {
    if (s != 0 && currentPhase != PHASE_NORMAL && currentPhase != PHASE_ITEM_USED )
        return false;

    bool flag = false;
    int stripe_side;

    if ( currentPhase == PHASE_NORMAL )
        for (auto& obj : m_Stage_Object) {
            if (obj) obj->SetAppearBool(true);
        }

    std::vector<std::vector<int>> total_length(m_Stage_Object.size(), std::vector<int>(6, 0));

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        int* neighbors = obj->GetInformationNeibor();
        obj->GetBlockType();

        

        if (obj->GetCurrentType() == RAINBOWBALL_OBJECT && obj->GetSwitchedInfo() == MOVE_BY_SWITCH) {
            obj->SetAppearBool(false);
        }

        if ((obj->GetCurrentType() == FLOWER_COMBINED_OBJECT || obj->GetCurrentType() == FLOWER_STRIPE_OBJECT || obj->GetCurrentType() == STRIPE_COMBINED_OBJECT) && obj->GetSwitchedInfo() == MOVE_BY_SWITCH) {
            obj->SetAppearBool(false);
        }

        for (int j = 0; j < 6; ++j) {
            int neighbor = neighbors[j]%(m_Size+1);
            if (neighbor == -1) continue;
            auto& neighbor_obj = m_Stage_Object[neighbor];
            if (!neighbor_obj) continue;

            if (IsSameColor(neighbor_obj->GetBlockType(), obj->GetBlockType()) &&
                neighbor_obj->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT &&
                neighbor_obj->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT &&
                obj->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT &&
                obj->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT) {
                total_length[i][j] = CheckNextAppearance(neighbor, j, 1);
            }
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfRainbowBall(i, total_length[i].data(), MOVE_BY_SWITCH)) {
            m_Stage_Object[i]->SetBlockType(RAINBOWBALL_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfRainbowBall(i, total_length[i].data(), MOVE_BY_DROP)) {
            m_Stage_Object[i]->SetBlockType(RAINBOWBALL_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfRainbowBall(i, total_length[i].data(), MOVE_BY_TOOL)) {
            m_Stage_Object[i]->SetBlockType(RAINBOWBALL_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfFlower(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(FLOWER_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfTriangleFlower(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(TRIANGLEFLOWER_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfStarFlower(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(STARFLOWER_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        stripe_side = DisappearMethodOfStripe(i, total_length[i].data(), MOVE_BY_SWITCH);
        if (stripe_side != -1) {
            if (stripe_side == 0 || stripe_side == 3)
                m_Stage_Object[i]->SetBlockType(STRIPE_OBJECT);
            else if (stripe_side == 1 || stripe_side == 4)
                m_Stage_Object[i]->SetBlockType(STRIPE_RIGHT_LEFT_OBJECT);
            else if (stripe_side == 2 || stripe_side == 5)
                m_Stage_Object[i]->SetBlockType(STRIPE_LEFT_RIGHT_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfStripe(i, total_length[i].data(), MOVE_BY_DROP) != -1) {
            m_Stage_Object[i]->SetBlockType(STRIPE_OBJECT);
        }
    }
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfStripe(i, total_length[i].data(), MOVE_BY_TOOL) != -1) {
            m_Stage_Object[i]->SetBlockType(STRIPE_OBJECT);
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (DisappearMethodOfOneLine(i, total_length[i].data())) {
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
    }
    
    
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (s == 0 && m_Stage_Object[i]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT )
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
    }


    for (auto& obj : m_Stage_Object) if (obj) obj->SetSwitched(NO_MOVE);

    for (auto& obj : m_Stage_Object) {
        if (obj && !obj->GetAppearBool()) flag = true;
    }

    CheckObstaclesDisappear(ifShuffle);

    if (flag || currentPhase == PHASE_ITEM_USED ) {
        if ( currentPhase == PHASE_NORMAL || currentPhase == PHASE_ITEM_USED ) {
            startTime = std::chrono::steady_clock::now();
            currentPhase = PHASE_BEFORE_DISAPPEAR;
        }
        if (s == 0 || ifShuffle) {
            MakeDisappear();
            Dropping(s, now_stage, ifShuffle);
        }
    } else {
        for (auto& obj : m_Stage_Object) if (obj) obj->SetSwitched(0);
        auto result = CheckShuffleDemands();
        if (result.first == -1 && result.second == -1) {
            if ( s == 0 || ifShuffle ) {
                ShuffleStageCharacter(now_stage);
                CheckAppearance(s, now_stage, true);
                AppearAll();
            }
            else 
                currentPhase = PHASE_SHUFFLE;
        }
    }

    return flag;
}

void StageObject::CheckSpecialObject(int i) {
    static const std::unordered_map<int, std::unordered_map<int, std::string>> imageMap = {
        {BLUE_OBJECT, {
            {STRIPE_OBJECT, BLUE_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, BLUE_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, BLUE_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, BLUE_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, BLUE_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, BLUE_TRIANGLEFLOWER_OBJECT}
        }},
        {BROWN_OBJECT, {
            {STRIPE_OBJECT, BROWN_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, BROWN_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, BROWN_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, BROWN_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, BROWN_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, BROWN_TRIANGLEFLOWER_OBJECT}
        }},
        {GREEN_OBJECT, {
            {STRIPE_OBJECT, GREEN_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, GREEN_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, GREEN_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, GREEN_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, GREEN_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, GREEN_TRIANGLEFLOWER_OBJECT}
        }},
        {PINK_OBJECT, {
            {STRIPE_OBJECT, PINK_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, PINK_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, PINK_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, PINK_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, PINK_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, PINK_TRIANGLEFLOWER_OBJECT}
        }},
        {ORANGE_OBJECT, {
            {STRIPE_OBJECT, ORANGE_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, ORANGE_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, ORANGE_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, ORANGE_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, ORANGE_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, ORANGE_TRIANGLEFLOWER_OBJECT}
        }},
        {WHITE_OBJECT, {
            {STRIPE_OBJECT, WHITE_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, WHITE_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, WHITE_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, WHITE_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, WHITE_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, WHITE_TRIANGLEFLOWER_OBJECT}
        }},
        {YELLOW_OBJECT, {
            {STRIPE_OBJECT, YELLOW_STRIPE_OBJECT},
            {STRIPE_LEFT_RIGHT_OBJECT, YELLOW_STRIPE_LEFT_RIGHT_OBJECT},
            {STRIPE_RIGHT_LEFT_OBJECT, YELLOW_STRIPE_RIGHT_LEFT_OBJECT},
            {FLOWER_OBJECT, YELLOW_FLOWER_OBJECT},
            {STARFLOWER_OBJECT, YELLOW_STARFLOWER_OBJECT},
            {TRIANGLEFLOWER_OBJECT, YELLOW_TRIANGLEFLOWER_OBJECT}
        }}
    };

    auto color = m_Stage_Object[i]->GetBlockType();
    auto type = m_Stage_Object[i]->GetType();

    if (type == RAINBOWBALL_OBJECT) {
        m_Stage_Object[i]->SetImage(RAINBOWBALL_OBJECT_LINK);
        m_Stage_Object[i]->SetBlock(0);
        return;
    }

    auto colorIt = imageMap.find(color);
    if (colorIt != imageMap.end()) {
        const auto& typeMap = colorIt->second;
        auto typeIt = typeMap.find(type);
        if (typeIt != typeMap.end()) {
            m_Stage_Object[i]->SetImage(typeIt->second);
        }
    }
}

void StageObject::CheckObstaclesDisappear(bool ifShuffle) {
    if ( ifShuffle )
        return;
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        auto& obj = m_Stage_Object[i];
        if (!obj) continue;

        if (obj->GetCurrentType() >= ONE_LAYER_COOKIE_OBJECT && obj->GetCurrentType() <= 50) {
            int* neighbors = obj->GetInformationNeibor();
            for (int j = 0; j < 6; ++j) {
                int neighborIdx = neighbors[j]%(m_Size+1);
                if (neighborIdx != -1 && neighborIdx < static_cast<int>(m_Stage_Object.size())) {
                    auto& neighbor = m_Stage_Object[neighborIdx];
                    if (neighbor && !neighbor->GetAppearBool() && neighbor->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                        MakeObstaclesDisappear(static_cast<int>(i));
                        break;
                    }
                }
            }
        }
    }
}

std::pair<int, int> StageObject::CheckShuffleDemands() {
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1);
            if (neighbor_no != -1 && neighbor_no < static_cast<int>(m_Stage_Object.size()) &&
                m_Stage_Object[i]->GetCurrentType() <= STRIPE_COMBINED_OBJECT &&
                m_Stage_Object[neighbor_no]->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);

                auto result = CheckRainbowUsing();
                if (result.first != -1 || result.second != -1) {
                    m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                    std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
                    return {result.first, result.second};
                }

                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
            }
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1);
            if (neighbor_no != -1 && neighbor_no < static_cast<int>(m_Stage_Object.size()) &&
                m_Stage_Object[i]->GetCurrentType() <= STRIPE_COMBINED_OBJECT &&
                m_Stage_Object[neighbor_no]->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);

                auto result = CheckSpecialBlocksNeighbor();
                if (result.first != -1 || result.second != -1) {
                    m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                    std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
                    return {result.first, result.second};
                }

                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
            }
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            const int neighbor_no = m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1);
            if (neighbor_no != -1 && neighbor_no < static_cast<int>(m_Stage_Object.size()) &&
                m_Stage_Object[i]->GetCurrentType() <= STRIPE_COMBINED_OBJECT &&
                m_Stage_Object[neighbor_no]->GetCurrentType() <= STRIPE_COMBINED_OBJECT) {
                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);

                if (CheckLineMaking()) {
                    m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                    std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
                    return {static_cast<int>(i), neighbor_no};
                }

                m_Stage_Object[i]->SwitchPosition(m_Stage_Object[neighbor_no]);
                std::swap(m_Stage_Object[i], m_Stage_Object[neighbor_no]);
            }
        }
    }

    return {-1, -1};
}

bool StageObject::CheckLineMaking() {
    for (size_t current_pos = 1; current_pos < m_Stage_Object.size(); ++current_pos) {
        for (int check_side = 0; check_side < 3; ++check_side) {
            int length = 1;

            if (m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1) != -1 &&
                IsSameColor(m_Stage_Object[current_pos]->GetBlockType(), m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1)]->GetBlockType())) {
                length += CheckNextAppearance(m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1), check_side, 1);
            }

            if (m_Stage_Object[current_pos]->GetInformationNeibor()[check_side + 3]%(m_Size+1) != -1 &&
                IsSameColor(m_Stage_Object[current_pos]->GetBlockType(), m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[check_side + 3]%(m_Size+1)]->GetBlockType())) {
                length += CheckNextAppearance(m_Stage_Object[current_pos]->GetInformationNeibor()[check_side + 3]%(m_Size+1), check_side + 3, 1);
            }

            if (length >= 3) return true;
        }
    }
    return false;
}

std::pair<int, int> StageObject::CheckRainbowUsing() {
    for (size_t current_pos = 1; current_pos < m_Stage_Object.size(); ++current_pos) {
        if (m_Stage_Object[current_pos]->GetCurrentType() == RAINBOWBALL_OBJECT) {
            for (int j = 0; j < 6; ++j) {
                if (m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) != -1)
                    return {static_cast<int>(current_pos), m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1)};
            }
        }
    }
    return {-1, -1};
}

std::pair<int, int> StageObject::CheckSpecialBlocksNeighbor() {
    for (size_t current_pos = 1; current_pos < m_Stage_Object.size(); ++current_pos) {
        if (m_Stage_Object[current_pos]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[current_pos]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT) {
            for (int j = 0; j < 6; ++j) {
                int neighbor = m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1);
                if (neighbor != -1 && neighbor < static_cast<int>(m_Stage_Object.size()) &&
                    m_Stage_Object[neighbor]->GetCurrentType() >= STRIPE_OBJECT && m_Stage_Object[neighbor]->GetCurrentType() <= TRIANGLEFLOWER_OBJECT) {
                    return {static_cast<int>(current_pos), neighbor};
                }
            }
        }
    }
    return {-1, -1};
}

bool StageObject::checkAppearanceOfObject ( int i, int side, int length_left) {
    bool return_bool = true;

    if( !m_Stage_Object[i]  )
        return false;

    if ( m_Stage_Object[i]->GetAppearBool() == true )
    {
        if( length_left >  0 )
        {
            return_bool = checkAppearanceOfObject (  m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) , side, length_left - 1);
            return return_bool;
        }
        else
        {
            return m_Stage_Object[i]->GetAppearBool();
        }
    }

    else{
        return false ;
    }
}

bool StageObject::checkSwitchedAllInfoWithZero ( int i, int side, int length_left) {
    if( !m_Stage_Object[i]  )
        return false;

    if ( m_Stage_Object[i]->GetSwitchedInfo() == 0 )
    {
        if( length_left >  0 )
            return checkSwitchedAllInfoWithZero ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1), side, length_left - 1) ;
        else
            return true;
    }
    else
        return false ;
}

int StageObject::CheckNextAppearance( int i, int side, int length ) {
    if (!m_Stage_Object[i] || m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 || !m_Stage_Object[ m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) ] )
        return length;

    if ( IsSameColor(m_Stage_Object[i]->GetBlockType() ,  m_Stage_Object[ m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) ]->GetBlockType()) &&  m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) != -1 ){
        return CheckNextAppearance(  m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) , side, length + 1 ) ;
    }
    else
        return length ;
}
