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

void StageObject::MakeDisappear() {
    if (m_Stage != 0 && currentPhase != PHASE_NORMAL && currentPhase != PHASE_ITEM_USED && currentPhase != PHASE_BEFORE_DISAPPEAR)
        return;
    
    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (!m_Stage_Object[i]->GetVisibility()) continue;
        
        if (!m_Stage_Object[i]->GetAppearBool() &&
        (m_Stage_Object[i]->GetCurrentType() == NORMAL_OBJECT ||
        m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT ||
        m_Stage_Object[i]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT ||
        m_Stage_Object[i]->GetGenerate())) {
            
            MakeDisappearWithObject(static_cast<int>(i));
            m_Stage_Object[i]->SetGenerate(false);
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if ((m_Stage_Object[i]->GetType() == NORMAL_OBJECT ||
             m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT) &&
             !m_Stage_Object[i]->GetAppearBool()) {
            if (m_Stage_Object[i]->GetCurrentType() != NORMAL_OBJECT)
                GoalUpdate(static_cast<int>(i));
            m_Stage_Object[i]->SetCurrentType(m_Stage_Object[i]->GetType());
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
        else if ( !m_Stage_Object[i]->GetAppearBool() &&
            m_Stage_Object[i]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT ) {
            m_Stage_Object[i]->SetCurrentType(ONE_LAYER_COOKIE_OBJECT);
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
            m_Stage_Object[i]->SetAppearBool( true );
            m_Stage_Object[i]->SetImage(COOKIE_ONE_IMAGE);
            m_Stage_Object[i]->SetBlock(NO_COLOR);
        } 
        else if (m_Stage_Object[i]->GetType() != NORMAL_OBJECT &&
                   !m_Stage_Object[i]->GetAppearBool()) {
            PointUpdate(GetPoint() + 1);
            GoalUpdate(static_cast<int>(i));
            m_Stage_Object[i]->SetAppearBool(true);
            CheckSpecialObject(static_cast<int>(i));
            m_Stage_Object[i]->SetGenerate(true);
            m_Stage_Object[i]->SetCurrentType(m_Stage_Object[i]->GetType());
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (!m_Stage_Object[i]->GetAppearBool()) {
            PointUpdate(GetPoint() + 1);
            GoalUpdate(static_cast<int>(i));
        }
    }

    // std::cout << "score: " << GetPoint() << std::endl;

    if ( stage_goal_counter[m_Stage] > 0  )
        currentPhase = PHASE_PAUSE_FOR_DISAPPEAR;
    startTime = std::chrono::steady_clock::now();
}

void StageObject::Dropping(int s, int now_stage, bool ifShuffle) {
    if (m_Stage != 0 && currentPhase != PHASE_DROPPING ) return;

    // is_click = 0;
    size_t loop_count = 0;
    for (size_t i = 1; i < m_Stage_Object.size();) {
        if (loop_count > m_Stage_Object.size() || !m_Stage_Object[i] || m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) == -1 || m_Stage_Object[i]->GetAppearBool()) {
            ++i;
            loop_count = 0;
            continue;
        }
        if (!m_Stage_Object[i]->GetAppearBool() && m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) != -1)
            Dropping_method(static_cast<int>(i));
        ++loop_count;
    }

    for (size_t i = 1; i < m_Stage_Object.size(); ++i) {
        if (!m_Stage_Object[i]->GetAppearBool() && m_Stage_Object[i]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT) {
            // // std::cout << "testing\n";
            m_Stage_Object[i]->SetImage(COOKIE_ONE_IMAGE);
            m_Stage_Object[i]->SetBlock(NO_COLOR);
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
        else if (!m_Stage_Object[i]->GetAppearBool()) {
            RandomChangeObject(static_cast<int>(i));
            m_Stage_Object[i]->SetBlockType(NORMAL_OBJECT);
        }
        m_Stage_Object[i]->SetAppearBool(true);
    }

    if (m_Stage != 0 ) AppearAll();
    // else if ( ifShuffle == true ) AppearAll();
    currentPhase = PHASE_NORMAL;
    CheckAppearance(s, now_stage, ifShuffle);
}

void StageObject::MakeObstaclesDisappear(int position) {

    //Add here if more obstacles
    switch ( m_Stage_Object[position]->GetCurrentType() ) {
        case ONE_LAYER_COOKIE_OBJECT:
            m_Stage_Object[position]->SetAppearBool(false);
        break;
        case TWO_LAYER_COOKIE_OBJECT:
            m_Stage_Object[position]->SetAppearBool(false);
        break;
    }
}

void StageObject::AppearAll() {
    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        m_Stage_Object.at(i)->SetVisible( true );
        m_Stage_Object.at(i)->SetAppearBool( true );
    }
    
}

void StageObject::DisAppearAll() {
    for (auto& obj : m_Stage_Object) {
        if (obj) {
            obj->SetAppearBool(false);
            obj->DisAppear();
        }
    }
    this->GetStageGoalObject()->DisAppear();
}

void StageObject::ClearAllClick() {
    for (auto& obj : m_Stage_Object) {
        if (obj) obj->SetClick(false);
    }
}


bool StageObject::DisappearMethodOfOneLine( int current_pos , int *total_length ) {

    bool cont_to_check = false ;

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) == 2 ) {

            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);


            //all side appear checked(true)
            if ( m_Stage_Object[current_pos]->GetAppearBool() == true && left_check == true && right_check == true )
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
               // cout<<"Line"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

                return cont_to_check;
            }

        }
        else if (total_length[i] + total_length[j]  > 2) // check all lines initial(line stripe rainbowball)
        {
            bool left_check_switch = true ;
            bool right_check_switch = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check_switch = checkSwitchedAllInfoWithZero( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check_switch = checkSwitchedAllInfoWithZero( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

            if (left_check_switch == true && right_check_switch == true && m_Stage_Object[current_pos]->GetAppearBool() == true)
            {
                cont_to_check = true ;
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

                return cont_to_check;
            }
        }
    }
    return cont_to_check;

}

int StageObject::DisappearMethodOfStripe( int current_pos, int* total_length, int priority ) {
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        // do not make true if it was checked
        if ( (total_length[i] + total_length[j] ) == 3 ) {
            bool left_check = true ;
            bool right_check = true ;
            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

            // check initial switch -> find switch side
            if (m_Stage_Object[current_pos]->GetSwitchedInfo() == MOVE_BY_SWITCH && priority == MOVE_BY_SWITCH && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

                //find initial neighbor side
                for ( int switch_side = 0  ; switch_side < 6 ; ++switch_side )
                {

                    if ( m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side]%(m_Size+1) != -1) {
                        if (m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[switch_side]%(m_Size+1) ]->GetSwitchedInfo() == 2 )
                        {
                           // cout << "Stripe" << endl;
                            return switch_side;
                        }
                    }
                }
            }
            else if (m_Stage_Object[current_pos]->GetSwitchedInfo() == MOVE_BY_DROP && priority == MOVE_BY_DROP && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                //all disappear
                m_Stage_Object[current_pos]->SetAppearBool( false );
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

               // cout << "Stripe" << endl;
                return 0;
            }
            else if ( m_Stage_Object[current_pos]->GetSwitchedInfo() == MOVE_BY_TOOL && priority == MOVE_BY_TOOL && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true)
            {
                //all disappear
                m_Stage_Object[current_pos]->SetAppearBool( false );
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

               // cout << "Stripe" << endl;
                return 0;
            }

        }
    }
    return -1;
}

bool StageObject::DisappearMethodOfFlower( int current_pos, int* total_length ) {

    bool cont_to_check = false ; //two side 1 + another 2
    int check_side = -1;

    for ( int i = 0  ; i < 6 ; ++i ) //another 2
    {
        if ( total_length[i] >= 2 )
        {
            bool checkside_check = true ;
            checkside_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

            if (checkside_check == true)
            {
                check_side = i ;
                break;
            }

        }
    }

    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( i != check_side && j != check_side && check_side != -1 )
        {
            bool left_check = true ;
            bool right_check = true ;

            //check all side appear
            if (total_length[i] > 0)
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) , i, total_length[i]-1);

            if (total_length[j] > 0)
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);

            if ( total_length[i] >= 1 && total_length[j] >= 1  && m_Stage_Object[current_pos]->GetAppearBool() == true  && left_check == true && right_check == true && check_side != -1) {//two side 1
                cont_to_check = true ;
                m_Stage_Object[current_pos]->SetAppearBool( false );
               // cout<<"Flower"<<endl;

                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[check_side]%(m_Size+1) , check_side, total_length[check_side]-1);
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1) , j, total_length[j]-1);
                break;
            }


        }
    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfStarFlower(  int current_pos, int* total_length ) {

    bool cont_to_check = false ; //two side 2
    int check_sides = 0;


    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( total_length[i] >= 1 && total_length[j] >= 1)
        {
            bool left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
            bool right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

            if (left_check == true && right_check == true )
                check_sides++ ;
        }
    }


    if (check_sides >= 2 && m_Stage_Object[current_pos]->GetAppearBool() == true)
    {
        for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j )
        {
            if (total_length[i] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
            if (total_length[j] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);
        }
        m_Stage_Object[current_pos]->SetAppearBool( false );
       // cout<<"Star Flower"<<endl;
        cont_to_check = true ;
    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfTriangleFlower( int current_pos , int* total_length ) {
    bool cont_to_check = false ; //two side >=2
    int check = 0;
    // two side >= 2
    for ( int i = 0  ; i < 6 ; ++i ) {
        if ( total_length[i] >= 2 ) {
            bool left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);

            if (left_check == true)
                check ++ ;
        }
    }

    if (check >= 2 && m_Stage_Object[current_pos]->GetAppearBool() == true)
    {
        m_Stage_Object[current_pos]->SetBlockType( TRIANGLEFLOWER_OBJECT );
        m_Stage_Object[current_pos]->SetAppearBool( false );
       // cout<<"Triangle Flower"<<endl;
        cont_to_check = true ;
        for ( int i = 0  ; i < 6 ; ++i )
        {
            if (total_length[i] > 0)
                DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
        }

    }

    return cont_to_check;
}

bool StageObject::DisappearMethodOfRainbowBall(  int current_pos, int* total_length, int priority ) {
    bool cont_to_check = false ;
    bool left_check = false;
    bool right_check = false;
    for ( int i = 0 , j = 3 ; i < 3 ; ++i, ++j ) {
        if ( (total_length[i] + total_length[j] ) >= 4 ) {

            if ( total_length[i] > 0 )
                left_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
            if ( total_length[j] > 0 )
                right_check = checkAppearanceOfObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);

            if (m_Stage_Object[current_pos]->GetSwitchedInfo() == priority && m_Stage_Object[current_pos]->GetAppearBool() == true && left_check == true && right_check == true)
            {
                m_Stage_Object[current_pos]->SetAppearBool( false );
               // cout<<"Rainbow Ball"<<endl;
                cont_to_check = true ;
                //all disappear(except switched blocks)
                if (total_length[i] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1), i, total_length[i]-1);
                if (total_length[j] > 0)
                    DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[j]%(m_Size+1), j, total_length[j]-1);
                return cont_to_check;
            }


        }
    }
    return cont_to_check;
}

void StageObject::DisappearBySingleObject( int current_pos, int side, int length_left) {
    m_Stage_Object[current_pos]->SetAppearBool( false );

    if( !m_Stage_Object[current_pos]  )
        return;

    if ( length_left  >  0 )
    {
        DisappearBySingleObject( m_Stage_Object[current_pos]->GetInformationNeibor()[side]%(m_Size+1), side, length_left - 1) ;
    }
}

void StageObject::Dropping_method( const int current_position ) {
    if ( !m_Stage_Object[current_position] || m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1) == -1  || !m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1)] || m_Stage_Object[current_position]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT || m_Stage_Object[current_position]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT )
        return;
    if ( current_position < m_Size+1 ) {
        int next_position; 
        if ( m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1) != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1)]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1)]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[0]%(m_Size+1);
        else if ( m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1) != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1)]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1)]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[5]%(m_Size+1);
        else if ( m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1) != -1 && ( m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1)]->GetCurrentType() != ONE_LAYER_COOKIE_OBJECT && m_Stage_Object[m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1)]->GetCurrentType() != TWO_LAYER_COOKIE_OBJECT ) )
            next_position = m_Stage_Object[current_position]->GetInformationNeibor()[1]%(m_Size+1);
        else
            return;
        bool flag = m_Stage_Object[next_position]->GetAppearBool();

        m_Stage_Object[current_position]->SetSwitched(1);
        m_Stage_Object[next_position]->SetSwitched(1);
        m_Stage_Object[current_position]->SwitchPosition( m_Stage_Object[next_position] );

        std::shared_ptr<GameCharacter> NewObject = m_Stage_Object[current_position];
        m_Stage_Object[current_position] = m_Stage_Object[next_position];
        m_Stage_Object[next_position] = NewObject;
        m_Stage_Object[current_position]->SetAppearBool( flag );
        
        Dropping_method( next_position );
    }

    return;
}