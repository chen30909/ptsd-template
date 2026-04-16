#include "GameCharacter.hpp"
#include "Util/Image.hpp"


GameCharacter::GameCharacter(const std::string& ImagePath)
    : Character(ImagePath), m_ImagePath(ImagePath) {}

void GameCharacter::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}