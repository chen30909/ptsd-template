#ifndef APP_HPP
#define APP_HPP
#include "pch.hpp"

#include "Util/Renderer.hpp"
#include "PhaseResourceManager.hpp"
#include "Character.hpp"
#include "GameCharacter.hpp"
#include "TaskText.hpp"
#include "StageObject.hpp"
#include "StageConfig.hpp"
#include "JumpPage.hpp"
#include "Item.hpp"
#include <vector>

bool PhaseInitialImage(std::shared_ptr<Character>& chara_obj);
int PhaseHomePage(const std::vector<std::shared_ptr<Character>>& buttoms);
bool PhaseStage(std::shared_ptr<StageObject> StageObject, int size, std::shared_ptr<TaskText> point, int stage , std::vector< std::shared_ptr<Item> > Tools );
void DebugPhaseStage1(std::vector<std::shared_ptr<GameCharacter>>& objectArray);

void DebugModeOfPosition(std::vector<std::shared_ptr<GameCharacter>>& objectArray, int option);
void DebugModeCancel(std::vector<std::shared_ptr<GameCharacter>>& objectArray, int option);
void DebugModeOfAppearance(const std::vector<std::shared_ptr<GameCharacter>>& objectArray, int size);
void DebugModeShowMapObject(const std::vector<std::shared_ptr<GameCharacter>>& objectArray, int size);

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }
    void Init();
    void Start();
    void Update();
    void End();
    void SetUpStage(int stage);
    void SetUpPlayStage( int m_stage_pos );
    void RemoveStage(int stage);
    void SetStage(int i) { m_stage_pos = i; }
    int GetStage() { return m_stage_pos; }


    void AppearHomePage() {

        m_Text_Point->SetVisible(false);
        m_Setting->SetVisible( true );

        const auto lastStage = static_cast<size_t>(GetPlayableStageCount());
        for (size_t i = 1; i < m_Stage_Buttoms.size() && i <= lastStage; ++i) {
            if (ifClear[i]) {
                m_Stage_Buttoms.at(i)->SetImage(ClearStageList[i]);
            }
            else if (i > 0 && ifClear[i - 1]) {
                m_Stage_Buttoms.at(i)->SetImage(CurrentStageList[i]);
            }
            else {
                m_Stage_Buttoms.at(i)->SetImage(LevelStageList[i]);
            }
            m_Stage_Buttoms.at(i)->SetVisible(true);
        }
    }

private:
    void Stage( int stage_pos );
    void WaitForShuffle(int stage_pos);
    void WaitBeforeDisappear(int stage_pos);
    void WaitForDisappearPause();
    void WaitForDrop(int stage_pos);
    void PassStage(int stage_pos);
    void StopStage(int stage_pos);
    void EndStage(int stage_pos);
    void FailStage(int stage_pos);
    void UseSelectedItem(int stage_pos);

private:
    enum class Phase {
        INITIAL_IMAGE = 1,
        HOME_PAGE = 2,
        STAGE = 3
    };

    State m_CurrentState = State::START;
    Phase m_Phase = Phase::INITIAL_IMAGE;

    Util::Renderer m_Root;
    std::shared_ptr<Character> m_Start_initial;
    std::shared_ptr<Character> m_Setting;
    std::vector<std::shared_ptr<Character>> m_Stage_Buttoms;
    std::vector<std::shared_ptr<StageObject>> m_Stage_Object;
    std::vector<std::shared_ptr<Item>> m_Tools;

    std::shared_ptr<JumpPage> m_Jump_Page;
    std::shared_ptr<TaskText> m_Text_Point;
    std::shared_ptr<TaskText> m_End_Point;
    std::shared_ptr<TaskText> m_Show_Text;
    std::shared_ptr<PhaseResourceManager> m_PRM;

    int m_stage_pos = 0;
    bool m_EnterDown = false;
};

#endif
