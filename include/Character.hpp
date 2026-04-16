#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>

#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Animation.hpp"
#include "Util/Image.hpp"
#include "Global.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    [[nodiscard]] virtual const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] virtual const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] virtual bool GetVisibility() const { return m_Visible; }

    virtual void SetImage(const std::string& ImagePath);

    virtual void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    virtual glm::vec2 GetSize() { return this->m_Size; }

    virtual void SetSize( glm::vec2 size ) { this->m_Size = size; }

    void SetAnimationPath( const std::vector<std::string>& AnimationPaths ) {
        m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 500, false, 0);
    }

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }
    [[nodiscard]] std::shared_ptr<Util::Animation> GetDrawable() {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    }
    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    [[nodiscard]] bool IfAnimationEnds() const {
        auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
    }

    [[nodiscard]] bool IfCollides(const std::shared_ptr<Character>& other) const {
        if (!other) return false;  
        glm::vec2 posA = GetPosition();
        glm::vec2 sizeA = this -> m_Size;
    
        glm::vec2 posB = other->GetPosition();
        glm::vec2 sizeB = this -> m_Size;
    
        bool collisionX = (posA.x < posB.x + sizeB.x) && (posA.x + sizeA.x > posB.x);
        bool collisionY = (posA.y < posB.y + sizeB.y) && (posA.y + sizeA.y > posB.y);
    
        return collisionX && collisionY;
    }
    
    [[nodiscard]] bool IfClick() {
        if ( currentPhase != PHASE_NORMAL && currentPhase != PHASE_ITEM_USED ) return false;
        glm::vec2 mousePos = Util::Input::GetCursorPosition();
    
        glm::vec2 pos = GetPosition();
        // std::cout << pos.x << " " << pos.y << std::endl;
        glm::vec2 size = this -> m_Size;
        bool insideX = (mousePos.x >= pos.x - size.x / 2.0f && mousePos.x <= pos.x + size.x / 2.0f);
        bool insideY = (mousePos.y >= pos.y - size.y / 2.0f && mousePos.y <= pos.y + size.y / 2.0f);
        bool isClicked = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);

        return insideX && insideY && isClicked;
    }
    
protected:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    glm::vec2 m_Size = { 50.0f, 50.0f };
    std::string m_ImagePath;
};


#endif //CHARACTER_HPP
