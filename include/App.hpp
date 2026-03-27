#ifndef APP_HPP
#define APP_HPP
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManager.hpp"
#include "Character.hpp"
#include "GameCharacter.hpp"
#include "ObjectInformation.hpp"
#include "TaskText.hpp"
#include "StageObject.hpp"
#include "JumpPage.hpp"
#include "Music.hpp"
#include "Item.hpp"
#include <vector>

bool PhaseInitialImage(std::shared_ptr<Character>& chara_obj);
int PhaseHomePage(const std::vector<std::shared_ptr<Character>>& buttoms);
bool PhaseStage(std::shared_ptr<StageObject> StageObject, int size, std::shared_ptr<TaskText> point, int stage , std::vector< std::shared_ptr<Item> > Tools );
// bool PhaseStage2(std::shared_ptr<StageObject> StageObject, int size, std::shared_ptr<TaskText> point);
void DebugPhaseStage1(std::vector<std::shared_ptr<GameCharacter>>& objectArray);

// Declare of Debug Mode
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
        if ( m_Jump_Page->ifBGM() )
            m_BGM_Music.at(0)->Playing(GA_RESOURCE_DIR "/Music/springDayShadow.mp3");

        m_Text_Point->SetVisible(false);
        m_Setting->SetVisible( true );

        // 修改迴圈上限，確保 i 不會超過 10，且不超過按鈕陣列實際大小
        for (size_t i = 1; i < m_Stage_Buttoms.size() && i < 11; ++i) {
            // 增加安全檢查，確保不會存取到 ifClear[11] 或 ifClear[12]
            if (i < 11) {
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
    }

private:
    void Stage( int stage_pos );

private:
    enum class Phase {
        INITIAL_IMAGE = 1,
        HOME_PAGE = 2,
        STAGE_1 = 3,
        STAGE_2 = 4,
        STAGE_3 = 5,
        STAGE_4 = 6,
        STAGE_5 = 7,
        STAGE_6 = 8,
        STAGE_7 = 9,
        STAGE_8 = 10,
        STAGE_9 = 11,
        STAGE_10 = 12
    };

    State m_CurrentState = State::START;
    Phase m_Phase = Phase::INITIAL_IMAGE;

    Util::Renderer m_Root;
    std::vector<std::shared_ptr<Music>> m_BGM_Music;
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
