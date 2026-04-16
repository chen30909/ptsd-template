#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

#include "Global.hpp"
#include "pch.hpp"
#include "ObjectInformation.hpp"
#include "Character.hpp"
#include "TaskText.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Animation.hpp"

#pragma once

class Item : public Character {
public:
    Item(const std::string& ImagePath)
        : Character(ImagePath), m_ImagePath(ImagePath) {
            this->SetSize({20, 25});
        }
    virtual ~Item() = default;

    int GetNum() { return m_Num; }
    
    bool ifClickInUse() { 
        return ( m_Num > 0 ) && ( this->IfClick() && this->GetVisibility() ); 
    }

    bool Click() {
        return m_Click;
    }
    void SetClick() {
        m_Click = true;
    }


    void UnClick() {
        m_Click = false;
    }
    
    std::shared_ptr<TaskText> GetText() {
        return m_ItemNumberShow;
    }

    void SetImage(const std::string& ImagePath) {
        m_ImagePath = ImagePath;
        
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    }
    
    void SetUp( int i ) {
        this->SetNum( item_num[i] );
        this->SetPosition( item_position[i] );
        this->SetVisible( false );
        m_ItemNumberShow = std::make_shared<TaskText>();
        m_ItemNumberShow->SetPosition( item_num_position[i] );
        m_ItemNumberShow->SetNum( this->GetNum() );
        m_ItemNumberShow->UpdateInItem();
        m_ItemNumberShow->SetVisible(false);
        m_ItemNumberShow->SetZIndex( 12 );
        this->SetZIndex( 5 );
    }

    void SetCheat( int i, int num ) {
        item_num[i] = this->GetNum();
        this->SetNum( num );
        m_ItemNumberShow->SetNum( this->GetNum() );
        m_ItemNumberShow->UpdateInItem();
        m_ItemNumberShow->SetZIndex( 12 );
        this->SetZIndex( 5 );
    }
    
    void Update() {
        this->SetNum( this->GetNum()-1 );
        m_ItemNumberShow->SetNum( this->GetNum() );
        m_ItemNumberShow->UpdateInItem();
        this->UnClick();
    }

    void Appear() {
        this->SetVisible( true );
        this->m_ItemNumberShow->SetVisible( true );
    }

    void Disappear() {
        this->SetVisible( false );
        this->m_ItemNumberShow->SetVisible( false );
    }
private:
    void SetNum( int num ) { m_Num = num; }
    int m_Num = 0;
    bool m_Click = false;

    std::string m_ImagePath;
    std::shared_ptr<TaskText> m_ItemNumberShow;
};

#endif // ITEM_HPP