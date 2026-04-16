#ifndef GAME_CHARACTER_HPP
#define GAME_CHARACTER_HPP

#include <string>
#include <iostream>

#include "Global.hpp"
#include "pch.hpp"
#include "ObjectInformation.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Animation.hpp"

class GameCharacter : public Character {
public:
    GameCharacter(const std::string& ImagePath);

    virtual ~GameCharacter() = default;

    void StartAnimationOnce() {
        AnimationInitail();
        std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->Play();
        if ( IfAnimationEnds() ) {
            std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->Pause();
        }
        SetImage( this->m_ImagePath );
    }

    void Appear() {
        this->SetVisible(true);
    }

    void DisAppear() {
        this->SetVisible(false);
    }
    
    void DebugMode(float Speed)
    {
        glm::vec2 NextPos = this->GetPosition();
        if (Util::Input::IsKeyDown(Util::Keycode::UP) )
            NextPos.y += Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::DOWN) )
            NextPos.y -= Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::LEFT) )
            NextPos.x -= Speed;
        if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) )
            NextPos.x += Speed;

        this->SetPosition( NextPos ); 
        std::cout << "x : " << NextPos.x << " y : " << NextPos.y << "\n";
    }
    
    Objectinformation GetInformation() { return this->m_information; }
    
    int GetInformationStage() { return (this->m_information).GetStage(); }

    int GetInformationPosNumber() { return (this->m_information).GetPositionNumber(); }

    int* GetInformationNeibor() { return (this->m_information).GetNeibor(); }

    int GetType() { return this->m_BlockType; }

    int GetCurrentType() { return this->m_CurrentType; }
    
    int GetBlockType() { return this->m_Block; }
    
    bool GetAppearBool() { return this->m_Appear; }
    
    glm::vec2 GetInformationPosition() { return (this->m_information).GetPosition(); }
    
    bool GetClick() {
        return this->m_Click;
    }
    int GetSwitchedInfo()
    {
        return this->m_Switched;
    }
    
    bool GetGenerate() {
        return this->m_Generate;
    }

    void SwitchPosition( std::shared_ptr<GameCharacter>& other ) {
        Objectinformation temp = this->m_information;
        this->m_information = other->m_information;
        other->m_information = temp;

        
        this->SetPosition( this->GetInformationPosition() );
        other->SetPosition( other->GetInformationPosition() );


        temp.~Objectinformation();

    }

    void SetCurrentType( int type ) {
        this->m_CurrentType = type;
    }
    void SetSwitched( int flag )
    {
        this->m_Switched = flag;
    }
    void SetInformation( Objectinformation& other ) {
        this->m_information = other;
    }

    void SetInformation( int Stage , int Pos , int* Neibor , const glm::vec2& Position) {
        (this->m_information).SetStage( Stage );
        (this->m_information).SetPosNumber( Pos );
        (this->m_information).SetNeibor( Neibor );
        this->SetPosition( Position );
    }
    virtual void SetPosition(const glm::vec2& Position) { 
        m_Transform.translation = Position; 
        (this->m_information).SetPosition( Position );
    }

    void SetBlock(int block_color) {
        this->m_Block = block_color;
    }

    void SetBlockType(int block_type) {
        this->m_BlockType = block_type;
    }
    
    void SetAppearBool( bool flag ) {
        this->m_Appear = flag;
    }

    void SetClick( bool flag ) {
        this->m_Click = flag;
    }
    
    void SetGenerate( bool flag ) {
        this->m_Generate = flag;
    }
    virtual void SetImage(const std::string& ImagePath);
protected:
    void ResetPosition() { 
        m_Transform.translation = {0, 0}; 
    }

    void AnimationInitail() {
        std::vector<std::string> AnimationPaths;
        AnimationPaths.push_back( this->m_ImagePath );
        AnimationPaths.push_back( EMPTY_OBJECT );
        AnimationPaths.push_back( this->m_ImagePath );
        AnimationPaths.push_back( EMPTY_OBJECT );
        m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 500, false, 0);
    }
    int m_Block = -1 ;
    int m_Switched = 0;
    glm::vec2 m_Size = { 50.0f, 100.0f };
    std::string m_ImagePath;
    Objectinformation m_information ;
    bool m_Appear = true;
    bool m_Click = false;
    int m_BlockType = 0;
    int m_CurrentType = 0;
    bool m_Generate = false;
};

#endif // GAME_CHARACTER_HPP