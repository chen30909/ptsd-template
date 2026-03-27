#include "pch.hpp"
#include "App.hpp"
#include "Global.hpp"


void App::Init() {
    InitializeStages();

    startTime = std::chrono::steady_clock::now();
    m_Stage_Object.resize( 13 );

    m_BGM_Music.resize(1);
    m_BGM_Music.at(0) = std::make_shared<Music>(GA_RESOURCE_DIR "/Music/springDayShadow.mp3");
    m_BGM_Music.at(0)->Pause();
    m_BGM_Music.at(0)->SetVolume(30);

    m_Start_initial = std::make_shared<Character>(GA_RESOURCE_DIR "/Image/GameObject/initailStartButton.png");
    m_Start_initial->SetPosition({0, -160.5f});
    m_Start_initial->SetZIndex(10);
    ADD(m_Start_initial);

    m_Setting = std::make_shared<Character>(GA_RESOURCE_DIR "/Image/GameObject/setting.png");
    m_Setting->SetPosition({0, -160.5f});
    m_Setting->SetZIndex(10);
    m_Setting->SetVisible( false );
    ADD(m_Setting);

    m_Stage_Buttoms.resize(13);
    const std::vector<std::string> levelImages = {
        "", LEVEL_ONE_IMAGE, LEVEL_TWO_IMAGE, LEVEL_THREE_IMAGE, LEVEL_FOUR_IMAGE,
        LEVEL_FIVE_IMAGE, LEVEL_SIX_IMAGE, LEVEL_SEVEN_IMAGE, LEVEL_EIGHT_IMAGE,
        LEVEL_NINE_IMAGE, LEVEL_TEN_IMAGE,// LEVEL_ELEVEN_IMAGE, LEVEL_TWELVE_IMAGE
    };
    for (int i = 1; i < 11; ++i)
    {
        m_Stage_Buttoms.at(i) = std::make_shared<Character>(levelImages.at(i));
        m_Stage_Buttoms.at(i)->SetPosition(stage_position[i]);
        m_Stage_Buttoms.at(i)->SetZIndex(10);
        m_Stage_Buttoms.at(i)->SetVisible(false);
        ADD(m_Stage_Buttoms.at(i));
    }

    m_Jump_Page = std::make_shared<JumpPage>(GA_RESOURCE_DIR "/Image/Background/stage1Start.png");
    m_Jump_Page->SetVisible(false);
    m_Jump_Page->SetPosition({0, 0});
    m_Jump_Page->SetZIndex(12);
    m_Jump_Page->SetSize({5, 5});
    ADD(m_Jump_Page);

    ADD(m_Jump_Page->GetPlayButtom());
    ADD(m_Jump_Page->GetCancelButtom());
    ADD(m_Jump_Page->GetPauseButtom());
    ADD(m_Jump_Page->GetStopButtom());
    ADD(m_Jump_Page->GetContinueButtom());
    ADD(m_Jump_Page->GetInfoButtom());
    ADD(m_Jump_Page->GetBGMButtom());
    ADD(m_Jump_Page->GetCheatButtom());


    m_Text_Point = std::make_shared<TaskText>();
    m_Text_Point->SetPosition({-125, 210});
    m_Text_Point->Initial(0);
    m_Text_Point->UpdateText();
    m_Text_Point->SetVisible(false);
    ADD(m_Text_Point);

    m_Show_Text = std::make_shared<TaskText>();
    m_Show_Text->Initial(0);
    m_Show_Text->SetPosition({0, -52.5});
    m_Show_Text->UpdateString("SHUFFLE!!!");
    m_Show_Text->SetVisible(false);
    m_Show_Text->SetZIndex( 30 );
    ADD(m_Show_Text);

    m_End_Point = std::make_shared<TaskText>();
    m_End_Point->SetPosition({0, -52.5});
    m_End_Point->Initial(0);
    m_End_Point->UpdateText();
    m_End_Point->SetVisible(false);
    ADD(m_End_Point);

    m_Tools.resize(3);
    m_Tools.at( HAMMER ) = std::make_shared<Item>( HAMMER_IMAGE );
    m_Tools.at( MAGIC_STICK ) = std::make_shared<Item>( MAGIC_STICK_IMAGE );
    m_Tools.at( GLOVES ) = std::make_shared<Item>( GLOVES_IMAGE );
    
    for ( int i = 0 ; i < 3 ; ++i ) {
        m_Tools.at(i)->SetUp( i );
        ADD( m_Tools.at(i)->GetText() );
        ADD( m_Tools.at(i) );
    }
    

    m_PRM = std::make_shared<PhaseResourceManager>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;
    m_BGM_Music.at(0)->Playing(GA_RESOURCE_DIR "/Music/aveMujica.mp3");
}