#ifndef PHASE_MANAGER_HPP
#define PHASE_MANAGER_HPP

#include "Util/GameObject.hpp"
// #include "TaskText.hpp"
// #include "Character.hpp"
#include "BackgroundImage.hpp"

class PhaseResourceManager {
public:
    PhaseResourceManager();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return {m_Background};
    }

    void NextPhase(int Phase);

    int ReturnPhase() { return m_Phase; }

private:
    // std::shared_ptr<TaskText> m_TaskText;
    std::shared_ptr<BackgroundImage> m_Background;

    int m_Phase = 2;
};


#endif //PHASE_MANGER_HPP