#include "App.hpp"
#include "Global.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    Init();
}

void App::Update() {
    switch (m_Phase) {
        case Phase::INITIAL_IMAGE:
            if (PhaseInitialImage(m_Start_initial)){
                m_PRM->NextPhase(PHASE_HOME_PAGE);
                m_Phase = Phase::HOME_PAGE;
                AppearHomePage();
                m_Jump_Page->AllDisappear();
            }
            break;
        case Phase::HOME_PAGE:
            {
                int get_stage = PhaseHomePage(m_Stage_Buttoms);
                if ( m_Setting->IfClick() ) {
                    m_Jump_Page->SettingPage();
                    m_Jump_Page->SetStatus( JUMP_SETTING );
                }
                else if ( get_stage != 0 && m_Jump_Page->GetStatus() != JUMP_SETTING ) {
                    m_stage_pos = get_stage;
                    m_Jump_Page->PlayPage( m_stage_pos );
                    m_Jump_Page->SetStatus( JUMP_PLAY );
                }
                if ( m_Jump_Page->GetStatus() == JUMP_SETTING && m_Jump_Page->ifClickWithBGM() ) {
                    if ( m_Jump_Page->ifBGM() ) {
                        m_Jump_Page->GetBGMButtom()->SetImage( OFF_IMAGE );
                        m_Jump_Page->SetBGM(false);
                    } else {
                        m_Jump_Page->GetBGMButtom()->SetImage( ON_IMAGE );
                        m_Jump_Page->SetBGM(true);
                    }
                }
                if ( m_Jump_Page->GetStatus() == JUMP_SETTING && m_Jump_Page->ifClickWithCheat() ) {
                    if ( m_Jump_Page->ifCheat() ) {
                        for ( int i = 0 ; i < 3 ; ++i ) {
                            m_Tools.at(i)->SetCheat( i , item_num[i] );
                        }
                        m_Jump_Page->GetCheatButtom()->SetImage( OFF_IMAGE );
                        m_Jump_Page->SetCheat(false);
                    } else {
                        for ( int i = 0 ; i < 3 ; ++i ) {
                            m_Tools.at(i)->SetCheat( i , 100 );
                        }
                        m_Jump_Page->GetCheatButtom()->SetImage( ON_IMAGE );
                        m_Jump_Page->SetCheat(true);
                    }
                }
                if ( m_Jump_Page->ifClickWithPlayButtom() ) {
                    SetUpStage( m_stage_pos );
                }
                if ( m_Jump_Page->ifClickWithInfoButtom() ) {
                    m_Jump_Page->AllDisappear();
                    m_Jump_Page->InfoPage( m_stage_pos );
                }
                if ( m_Jump_Page->ifClickWithCancelButtom() && m_Jump_Page->GetStatus() == JUMP_INFO ) {
                    m_Jump_Page->AllDisappear();
                    m_Jump_Page->PlayPage( m_stage_pos );
                    m_Jump_Page->SetStatus( JUMP_PLAY );
                }
                else if ( m_Jump_Page->ifClickWithCancelButtom() && m_Jump_Page->GetStatus() == JUMP_SETTING ) {
                    m_Jump_Page->AllDisappear();
                    m_Jump_Page->SetStatus( JUMP_NORMAL );
                    m_stage_pos = 0;
                }
                else if (m_Jump_Page->ifClickWithCancelButtom() && m_Jump_Page->GetStatus() == JUMP_PLAY ) {
                    m_Jump_Page->AllDisappear();
                    m_Jump_Page->SetStatus( JUMP_NORMAL );
                    m_stage_pos = 0;
                }
            }
            break;

        case Phase::STAGE:
            Stage( m_stage_pos );
            break;


        }


    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
    Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::End() {
    LOG_TRACE("End");
}
