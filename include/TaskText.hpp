#ifndef TASKTEXT_HPP
#define TASKTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include <string>

class TaskText : public Util::GameObject {
public:
    TaskText() : GameObject(
            std::make_unique<Util::Text>(GA_RESOURCE_DIR "/Font/Inkfree.ttf", 15,
                                         append_string_views("0", ""),
                                         Util::Color::FromName(Util::Colors::BLUE)),
            100) {
        m_Transform.translation = {0.0F, -270.F};
    }

    void Initial( int stage ) {
        stage_goal_counter[stage] = stage_point_goal[stage];
        this->m_Point = 0;
        this->m_Movement = stage_moves[stage];
        this->m_Goal = stage_point_goal[stage];
        this->m_goal_des = stage_goal_type[stage];
        this->SetPosition( point_position[stage] );
        this->UpdateText();
    }
    bool GetVisibility() const { return m_Visible; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    int GetPoint() { return this->m_Point; }

    int GetGoal() { return this->m_Goal; }

    int GetMove() { return this->m_Movement; }
    
    void SetPoint(int point) {
        this->m_Point = point;
    }

    void SetGoal( int goal ) {
        this->m_Goal = goal;
    }

    void SetMove( int move ) {
        this->m_Movement = move;
    }

    void UpdateText() {  
        auto* temp = dynamic_cast<Util::Text*>(m_Drawable.get());
        if (temp) {
            temp->SetText(show_string( m_goal_des , m_Goal , m_Movement , m_Point ));
        }
    }

    void UpdateEndPoint( int point ) {  
        auto* temp = dynamic_cast<Util::Text*>(m_Drawable.get());
        if (temp) {
            temp->SetText(endpoint_string( point ));
        }
    }

    void SetNum( int num ) { m_Num = num; }
    void UpdateInItem() {  
        auto* temp = dynamic_cast<Util::Text*>(m_Drawable.get());
        if (temp) {
            temp->SetText( std::to_string( m_Num ) );
        }
    }

    void UpdateString( std::string s ) {
        auto* temp = dynamic_cast<Util::Text*>(m_Drawable.get());
        if (temp) {
            temp->SetText( s );
        }
    }

private:
    inline static std::string append_string_views(const std::string& sv1, const std::string& sv2) {
        return sv1 + "\n" + sv2;
    }

    inline static std::string show_string(std::string goal_descript , int goal , int move , int point ) {
        return  "          " + std::to_string(goal) + "                         " + std::to_string(move) + "       Point: " + std::to_string(point) + "\n\n\nGoal Description: \n" + goal_descript + "\n" ;
    }

    inline static std::string endpoint_string( int point ) {
        return "Point : " + std::to_string( point ) + "\n"; 
    }

    int m_Point = 0;
    int m_Goal = 0;
    int m_Movement = 0;
    int m_Num = 0;
    std::string m_goal_des;
};

#endif // TASKTEXT_HPP