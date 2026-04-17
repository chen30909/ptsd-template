#include "App.hpp"
#include "Global.hpp"
#include "StageConfig.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::WaitForShuffle(int stage_pos) {
    m_Show_Text->SetVisible(true);
    if (WAIT_FOR_SECOND(3)) {
        m_Stage_Object[stage_pos]->ShuffleStageCharacter(stage_pos);
        m_Show_Text->SetVisible(false);
        currentPhase = PHASE_NORMAL;
    }
    m_Stage_Object[stage_pos]->CheckAppearance(1, stage_pos, true);
    m_Stage_Object[stage_pos]->AppearAll();
}

void App::WaitBeforeDisappear(int stage_pos) {
    if (WAIT_FOR_SECOND(1)) {
        currentPhase = PHASE_NORMAL;
        m_Stage_Object[stage_pos]->MakeDisappear();
    }
    m_Root.Update();
}

void App::WaitForDisappearPause() {
    if (WAIT_FOR_SECOND(1)) {
        currentPhase = PHASE_DROPPING;
    }
    m_Root.Update();
}

void App::WaitForDrop(int stage_pos) {
    m_Stage_Object[stage_pos]->Dropping(stage_pos, stage_pos, false);
    m_Text_Point->SetPoint(stage_point_counter[stage_pos]);
    if (stage_pos != 3 && stage_pos != 4) {
        m_Text_Point->SetGoal(stage_goal_counter[stage_pos]);
    }
    m_Text_Point->UpdateText();
}

void App::PassStage(int stage_pos) {
    m_Stage_Object[stage_pos]->DisAppearAll();
    m_Text_Point->SetVisible(false);
    m_End_Point->UpdateEndPoint(stage_point_counter[stage_pos]);
    m_End_Point->SetVisible(true);
    ifClear[stage_pos] = true;
    m_Jump_Page->EndPage(stage_pos);
    m_Jump_Page->SetStatus(JUMP_END);
}

void App::StopStage(int stage_pos) {
    m_Jump_Page->AllDisappear();
    m_PRM->NextPhase(PHASE_HOME_PAGE);
    RemoveStage(stage_pos);
    m_Phase = Phase::HOME_PAGE;
    AppearHomePage();
    m_Stage_Object[stage_pos]->DisAppearAll();
    stage_point_counter[stage_pos] = 0;
    m_stage_pos = 0;
    m_Text_Point->SetVisible(false);
    for (int i = 0; i < 3; ++i) {
        m_Tools.at(i)->Disappear();
    }
}

void App::EndStage(int stage_pos) {
    m_Jump_Page->AllDisappear();
    m_End_Point->SetVisible(false);
    m_PRM->NextPhase(PHASE_HOME_PAGE);
    RemoveStage(stage_pos);
    m_Phase = Phase::HOME_PAGE;
    AppearHomePage();
    stage_point_counter[stage_pos] = 0;
    m_stage_pos = 0;
    for (int i = 0; i < 3; ++i) {
        m_Tools.at(i)->Disappear();
    }
}

void App::FailStage(int stage_pos) {
    m_Stage_Object[stage_pos]->DisAppearAll();
    m_Text_Point->SetVisible(false);
    ifClear[stage_pos] = false;
    m_Jump_Page->FailPage(stage_pos);
}

void App::UseSelectedItem(int stage_pos) {
    for (int tool_idx = 0; tool_idx < 3; ++tool_idx) {
        if (!m_Tools.at(tool_idx)->Click()) {
            continue;
        }

        if (tool_idx == HAMMER) {
            m_Stage_Object.at(stage_pos)->UseHammer(m_Tools.at(HAMMER));
        } else if (tool_idx == MAGIC_STICK) {
            m_Stage_Object.at(stage_pos)->UseMagicStick(m_Tools.at(MAGIC_STICK));
        } else if (tool_idx == GLOVES) {
            m_Stage_Object.at(stage_pos)->UseMagicGlove(m_Tools.at(GLOVES));
        }
    }
}

void App::SetUpStage(int stage) {
    // m_Stage_Object.at(stage)->ClearObject();
    m_Setting->SetVisible(false);
    if (!IsPlayableStage(stage)) return;

    const auto& config = GetStageConfig(stage);
    int size = config.boardSize;
    
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
    
    auto stage_goal = std::make_shared<GameCharacter>(config.goalImage);
    stage_goal->SetPosition(stage_goal_position[stage]);
    stage_goal->SetVisible(config.hasBoard);
    stage_goal->SetZIndex( 10 );
    ADD(stage_goal);
    m_Stage_Object.at(stage)->SetStageGoalObject( stage_goal );
    
    for (auto& btn : m_Stage_Buttoms) 
        if ( btn )
            btn->SetVisible(false);
    m_Jump_Page->AllDisappear();
    m_Jump_Page->GetPauseButtom()->SetVisible(true);
    m_Text_Point->SetPoint(0);
    m_Text_Point->SetVisible(config.hasBoard);
    SetUpPlayStage(stage);
}

void App::SetUpPlayStage(int m_stage_pos) {
    if (!IsPlayableStage(m_stage_pos)) return;

    if (HasStageBoard(m_stage_pos)) {
        m_Stage_Object[m_stage_pos]->SetUp(m_stage_pos);
        m_Stage_Object[m_stage_pos]->AppearAll();
    }
    m_Stage_Object[m_stage_pos]->SetStage(m_stage_pos);
    m_Text_Point->Initial(m_stage_pos);
    m_Show_Text->Initial(m_stage_pos);
    m_End_Point->Initial(m_stage_pos);
    m_Show_Text->UpdateString("SHUFFLE!!!");
    m_End_Point->SetPosition({5, -52.5});
    m_Show_Text->SetPosition({0, 250});
    m_Jump_Page->AllDisappear();

    currentPhase = PHASE_NORMAL;
    m_PRM->NextStage(m_stage_pos);
    m_Phase = Phase::STAGE;
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
    if (!HasStageBoard(stage_pos)) {
        if ( m_Jump_Page->ifClickWithPauseButtom() ) m_Jump_Page->PausePage();
        if ( m_Jump_Page->ifClickWithContinueButtom() ) m_Jump_Page->AllDisappear();
        if ( m_Jump_Page->ifClickWithStopButtom() ) StopStage(stage_pos);
        return;
    }

    if ( m_Jump_Page->GetStatus() != JUMP_END && (stage_goal_counter[stage_pos] <= 0 || PhaseStage( m_Stage_Object[stage_pos], m_Stage_Object[stage_pos]->GetSize() , m_Text_Point , stage_pos , m_Tools) )) 
        PassStage(stage_pos);
    else if ( (m_Text_Point->GetMove() <= 0 && stage_goal_counter[stage_pos] > 0) && currentPhase == PHASE_NORMAL ) FailStage(stage_pos);
    else if ( currentPhase == PHASE_ITEM_USED ) UseSelectedItem(stage_pos);
    else if ( currentPhase == PHASE_SHUFFLE ) WaitForShuffle(stage_pos);
    else if ( currentPhase == PHASE_BEFORE_DISAPPEAR ) WaitBeforeDisappear(stage_pos);
    else if ( currentPhase == PHASE_PAUSE_FOR_DISAPPEAR ) WaitForDisappearPause();
    else if ( currentPhase == PHASE_DROPPING ) WaitForDrop(stage_pos);
    if ( m_Jump_Page->ifClickWithPauseButtom() ) m_Jump_Page->PausePage();
    if ( m_Jump_Page->ifClickWithContinueButtom() ) m_Jump_Page->AllDisappear();
    if ( m_Jump_Page->ifClickWithStopButtom() ) StopStage(stage_pos);
    if ( m_Jump_Page->ifClickWithCancelButtomInEnd() ) EndStage(stage_pos);
}
