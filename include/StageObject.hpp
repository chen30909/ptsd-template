#ifndef STAGE_OBJECT_HPP
#define STAGE_OBJECT_HPP

#include "pch.hpp"
#include <vector>

class StageObject {
public:
    struct Slot {
        int id = 0;
        glm::vec2 position = {0.0f, 0.0f};
        float radius = 28.0f;
    };

    StageObject();

    void InitStage1();
    const std::vector<Slot>& GetSlots() const;

private:
    std::vector<Slot> m_Slots;
};

#endif