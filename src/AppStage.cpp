#include "App.hpp"
#include "Global.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#define WAIT_FOR_SHUFFLE(stage_pos) do { \
    m_Show_Text->SetVisible(true); \
    if (WAIT_FOR_SECOND(3)) { \
        m_Stage_Object[stage_pos]->ShuffleStageCharacter(stage_pos); \
        m_Show_Text->SetVisible(false); \
        currentPhase = PHASE_NORMAL; \
    } \
    m_Stage_Object[stage_pos]->CheckAppearance(1, stage_pos, true); \
    m_Stage_Object[stage_pos]->AppearAll(); \
} while(0)

#define WAIT_FOR_BEF_DIS(stage_pos) do { \
    if (WAIT_FOR_SECOND(1)) { \
        currentPhase = PHASE_NORMAL; \
        m_Stage_Object[stage_pos]->MakeDisappear(); \
    } \
    m_Root.Update(); \
} while(0)

#define WAIT_FOR_DIS do { \
    if ( WAIT_FOR_SECOND(1) ) { \
                currentPhase = PHASE_DROPPING; \
            } \
            m_Root.Update(); \
} while(0)

#define WAIT_FOR_DROP(stage_pos) do { \
    m_Stage_Object[stage_pos]->Dropping(stage_pos, stage_pos, false); \
    m_Text_Point->SetPoint(stage_point_counter[stage_pos]); \
    if (stage_pos != 3 && stage_pos != 4) \
        m_Text_Point->SetGoal(stage_goal_counter[stage_pos]); \
    m_Text_Point->UpdateText(); \
} while(0)

#define PASS(stage_pos) do { \
    m_Stage_Object[(stage_pos)]->DisAppearAll(); \
    m_Text_Point->SetVisible(false); \
    m_End_Point->UpdateEndPoint(stage_point_counter[(stage_pos)]); \
    m_End_Point->SetVisible(true); \
    ifClear[(stage_pos)] = true; \
    m_Jump_Page->EndPage((stage_pos)); \
    m_Jump_Page->SetStatus(JUMP_END); \
} while(0)

#define STOP(stage_pos) do { \
    m_Jump_Page->AllDisappear(); \
    m_PRM->NextPhase(PHASE_HOME_PAGE); \
    RemoveStage(stage_pos); \
    m_Phase = Phase::HOME_PAGE; \
    AppearHomePage(); \
    m_Stage_Object[stage_pos]->DisAppearAll(); \
    stage_point_counter[stage_pos] = 0; \
    m_stage_pos = 0; \
    m_Text_Point->SetVisible(false); \
    for (int i = 0; i < 3; ++i) { \
        m_Tools.at(i)->Disappear(); \
    } \
} while(0)

#define END(stage_pos) do { \
    m_Jump_Page->AllDisappear(); \
    m_End_Point->SetVisible(false); \
    m_PRM->NextPhase(PHASE_HOME_PAGE); \
    RemoveStage(stage_pos); \
    m_Phase = Phase::HOME_PAGE; \
    AppearHomePage(); \
    stage_point_counter[stage_pos] = 0; \
    m_stage_pos = 0; \
    for (int i = 0; i < 3; ++i) { \
        m_Tools.at(i)->Disappear(); \
    } \
} while(0)

#define FAIL(stage_pos) do { \
    m_Stage_Object[(stage_pos)]->DisAppearAll(); \
    m_Text_Point->SetVisible(false); \
    ifClear[(stage_pos)] = false; \
    m_Jump_Page->FailPage((stage_pos)); \
} while(0)

#define JUMP_PAUSE m_Jump_Page->PausePage()

#define JUMP_CONTINUE m_Jump_Page->AllDisappear();

#define ITEM_USED do { \
    for (int tool_idx = 0; tool_idx < 3; ++tool_idx) { \
        if (m_Tools.at(tool_idx)->Click()) { \
            if (tool_idx == HAMMER) { \
                m_Stage_Object.at(stage_pos)->UseHammer(m_Tools.at(HAMMER)); \
            } else if (tool_idx == MAGIC_STICK) { \
                m_Stage_Object.at(stage_pos)->UseMagicStick(m_Tools.at(MAGIC_STICK)); \
            } else if (tool_idx == GLOVES) { \
                m_Stage_Object.at(stage_pos)->UseMagicGlove(m_Tools.at(GLOVES)); \
            } \
        } \
    } \
} while(0)


void App::SetUpStage(int stage) {
    // m_Stage_Object.at(stage)->ClearObject();
    m_Setting->SetVisible(false);
    if ( m_Jump_Page->ifBGM() )
        m_BGM_Music.at(0)->Playing(RESOURCE_DIR "/Music/rickRoll.mp3");
    int size = 0;
    if (stage == 1) size = 37;
    else if (stage == 2) size = 45;
    else if (stage == 3) size = 47;
    else if (stage == 4) size = 64;
    else if (stage == 5) size = 39;
    else if (stage == 6) size = 72;
    else if (stage == 7) size = 60;
    else if (stage == 8) size = 70;
    else if (stage == 9) size = 43;
    else if (stage == 10) size = 73;
    //else if (stage == 11) size = 59;
    //else if (stage == 12) size = 69;
    
    if (m_Stage_Object.size() <= static_cast<size_t>(stage)) m_Stage_Object.resize(stage + 1);
    m_Stage_Object.at(stage) = std::make_shared<StageObject>(size);
    m_Stage_Object.at(stage)->SetStage(0);
    auto clickObj = std::make_shared<GameCharacter>(RESOURCE_DIR "/Image/GameObject/click.png");
    clickObj->SetVisible(false);
    clickObj->SetZIndex(9);
    m_Stage_Object[stage]->PushBackObject(clickObj);
    ADD(clickObj);
    
    for (int i = 1; i <= size; ++i) {
        auto obj = std::make_shared<GameCharacter>(BLUE_NORMAL_OBJECT);
        obj->SetVisible(false);
        obj->SetZIndex(10);
        m_Stage_Object.at(stage)->PushBackObject(obj); // 先收集
        ADD(obj);
    }
    
    ADD(m_Stage_Object.at(stage));
    
    auto goalImage = (stage >= 3) ? REACH_IMAGE : BROWN_NORMAL_OBJECT;
    auto stage_goal = std::make_shared<GameCharacter>(goalImage);
    if ( stage == 1 || stage == 2 ) 
        stage_goal->SetImage( BROWN_NORMAL_OBJECT );
    else if ( stage == 3 || stage == 4 )
        stage_goal->SetImage( REACH_IMAGE );
    else if ( stage == 5 || stage == 6 || stage == 7 /*|| stage == 11 */ )
        stage_goal->SetImage( COOKIE_ONE_IMAGE );
    else if ( stage == 8 )
        stage_goal->SetImage( WHITE_STARFLOWER_OBJECT );
    else if ( stage == 9 || stage == 10 )
        stage_goal->SetImage( WHITE_STRIPE_OBJECT );
    /*else if ( stage == 12 )
        stage_goal->SetImage( RAINBOWBALL_OBJECT_LINK );
*/
    stage_goal->SetPosition(stage_goal_position[stage]);
    stage_goal->SetVisible(true);
    stage_goal->SetZIndex( 10 );
    ADD(stage_goal);
    m_Stage_Object.at(stage)->SetStageGoalObject( stage_goal );
    
    for (auto& btn : m_Stage_Buttoms) 
        if ( btn )
            btn->SetVisible(false);
    m_Jump_Page->AllDisappear();
    m_Jump_Page->GetPauseButtom()->SetVisible(true);
    m_Text_Point->SetPoint(0);
    m_Text_Point->SetVisible(true);
    SetUpPlayStage(stage);
}

void App::SetUpPlayStage( int m_stage_pos ) {
    if ( m_stage_pos >= 1 && m_stage_pos <= 12 ) { 
        m_Stage_Object[m_stage_pos]->SetUp( m_stage_pos );
        m_Stage_Object[m_stage_pos]->AppearAll();
        m_Stage_Object[m_stage_pos]->SetStage( m_stage_pos );
        m_Text_Point->Initial( m_stage_pos );
        m_Show_Text->Initial( m_stage_pos );
        m_End_Point->Initial( m_stage_pos );
        m_Show_Text->UpdateString("SHUFFLE!!!");
        m_End_Point->SetPosition( { 5 , -52.5 });
        m_Show_Text->SetPosition( {0, 250});
        m_Jump_Page->AllDisappear();
        if ( ifClear[7] || m_Jump_Page->ifCheat()) {
            m_Tools[1]->SetImage( MAGIC_STICK_IMAGE );
            m_Tools[1]->UnClick();
            m_Tools[1]->Appear();
        }
        if ( ifClear[8] || m_Jump_Page->ifCheat() ) {
            m_Tools[2]->SetImage( GLOVES_IMAGE );
            m_Tools[2]->UnClick();
            m_Tools[2]->Appear();
        } 
        if ( ifClear[9] || m_Jump_Page->ifCheat() ) {
            m_Tools[0]->SetImage( HAMMER_IMAGE );
            m_Tools[0]->UnClick();
            m_Tools[0]->Appear();
        }

        currentPhase = PHASE_NORMAL;
        if ( m_stage_pos == 1  ) {
            std::cout << "Level1 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_1);
            m_Phase = Phase::STAGE_1;
        }
        else if ( m_stage_pos == 2 ) {
            std::cout << "Level2 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_2);
            m_Phase = Phase::STAGE_2;
        }
        else if ( m_stage_pos == 3 ) {
            std::cout << "Level3 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_3);
            m_Phase = Phase::STAGE_3;
        }
        else if ( m_stage_pos == 4 ) {
            std::cout << "Level4 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_4);
            m_Phase = Phase::STAGE_4;
        }
        else if ( m_stage_pos == 5 ) {
            std::cout << "Level5 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_5);
            m_Phase = Phase::STAGE_5;
        }
        else if ( m_stage_pos == 6 ) {
            std::cout << "Level6 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_6);
            m_Phase = Phase::STAGE_6;
        }
        else if ( m_stage_pos == 7 ) {
            std::cout << "Level7 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_7);
            m_Phase = Phase::STAGE_7;
        }
        else if ( m_stage_pos == 8 ) {
            std::cout << "Level8 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_8);
            m_Phase = Phase::STAGE_8;
        }
        else if ( m_stage_pos == 9 ) {
            std::cout << "Level9 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_9);
            m_Phase = Phase::STAGE_9;
        }
        else if ( m_stage_pos == 10 ) {
            std::cout << "Level10 Character clicked!" << std::endl;
            m_PRM->NextPhase(PHASE_STAGE_10);
            m_Phase = Phase::STAGE_10;
        }
    }
}

void App::RemoveStage(int stage) {
    for ( int i = 0 ; i < m_Stage_Object.at(stage)->GetSize()+1 ; ++i ){
        m_Root.RemoveChild( m_Stage_Object.at(stage)->GetStageObjectItem(i) );
    }
    m_Stage_Object.at(stage)->ClearAll();
    m_Root.RemoveChild(m_Stage_Object.at(stage)->GetStageGoalObject());
    if (static_cast<size_t>(stage) < m_Stage_Object.size()) {
        m_Root.RemoveChild(m_Stage_Object.at(stage));
    }
}

void App::Stage( int stage_pos ) {
    m_Jump_Page->GetPauseButtom()->SetVisible( true );
    if ( m_Jump_Page->GetStatus() != JUMP_END && (stage_goal_counter[stage_pos] <= 0 || PhaseStage( m_Stage_Object[stage_pos], m_Stage_Object[stage_pos]->GetSize() , m_Text_Point , stage_pos , m_Tools) )) 
        PASS(stage_pos);
    else if ( (m_Text_Point->GetMove() <= 0 && stage_goal_counter[stage_pos] > 0) && currentPhase == PHASE_NORMAL ) FAIL(stage_pos);
    else if ( currentPhase == PHASE_ITEM_USED ) ITEM_USED;
    else if ( currentPhase == PHASE_SHUFFLE ) WAIT_FOR_SHUFFLE(stage_pos);
    else if ( currentPhase == PHASE_BEFORE_DISAPPEAR ) WAIT_FOR_BEF_DIS(stage_pos);
    else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) WAIT_FOR_DIS;
    else if ( currentPhase == PHASE_DROPPING ) WAIT_FOR_DROP(stage_pos);
    if ( m_Jump_Page->ifClickWithPauseButtom() ) JUMP_PAUSE;
    if ( m_Jump_Page->ifClickWithContinueButtom() ) JUMP_CONTINUE;
    if ( m_Jump_Page->ifClickWithStopButtom() ) STOP(stage_pos);
    if ( m_Jump_Page->ifClickWithCancelButtomInEnd() ) END(stage_pos);
}