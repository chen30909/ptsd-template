#include "App.hpp"
#include "PhaseResourceManager.hpp"
#include "Global.hpp"
#include "Util/Logger.hpp"

PhaseResourceManager::PhaseResourceManager() {
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManager::NextPhase(int Phase) {
    LOG_DEBUG("Passed! Next phase: {}", Phase);
    switch (Phase){
        case PHASE_HOME_PAGE:
            m_Background->NextImage("homePage.png");
            m_Phase = Phase;
            break; 
        case PHASE_STAGE_1:
            m_Background->NextImage("first.png");
            m_Phase = Phase;
            break;
        case PHASE_STAGE_2:
            m_Background->NextImage("second.png");
            m_Phase = Phase;
            break;

        case PHASE_STAGE_3:
            m_Background->NextImage("third.png");
            m_Phase = Phase;
            break;

        case PHASE_STAGE_4:
            m_Background->NextImage("fourth.png");
            m_Phase = Phase;
            break;

        case PHASE_STAGE_5:
            m_Background->NextImage("fifth.png");
            m_Phase = Phase;
            break;

        case PHASE_STAGE_6:
            m_Background->NextImage("sixth.png");
            m_Phase = Phase;
            break;
        
        case PHASE_STAGE_7:
            m_Background->NextImage("seventh.png");
            m_Phase = Phase;
            break;

        case PHASE_STAGE_8:
            m_Background->NextImage("eighth.png");
            m_Phase = Phase;
            break;

        case PHASE_STAGE_9:
            m_Background->NextImage("ninth.png");
            m_Phase = Phase;
            break;
        case PHASE_STAGE_10:
            m_Background->NextImage("tenth.png");
            m_Phase = Phase;
            break;
    }
}
