#include "App.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_INFO("App Start");

    m_FirstStageImage = std::make_shared<Util::GameObject>(
        std::make_shared<Util::Image>(std::string(RESOURCE_DIR) + "/Image/Background/first.png"),
        0.0f
    );

    m_FirstStageImage->m_Transform.translation = {0.0f, 0.0f};
    m_FirstStageImage->m_Transform.scale = {1.0f, 1.0f};

    m_Root.AddChild(m_FirstStageImage);

    m_Stage.InitStage1();

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}

void App::End() {
    LOG_INFO("App End");
}