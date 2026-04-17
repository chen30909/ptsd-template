#include "App.hpp"
#include "PhaseResourceManager.hpp"
#include "Global.hpp"
#include "StageConfig.hpp"
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
        case PHASE_STAGE:
            m_Background->NextImage("first.png");
            m_Phase = Phase;
            break;

    }
}

void PhaseResourceManager::NextStage(int stage) {
    const auto& config = GetStageConfig(stage);
    LOG_DEBUG("Passed! Next stage: {}", stage);
    m_Background->NextImage(config.backgroundImage);
    m_Phase = PHASE_STAGE;
}
