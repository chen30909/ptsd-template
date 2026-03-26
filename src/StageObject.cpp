#include "StageObject.hpp"

StageObject::StageObject() = default;

void StageObject::InitStage1() {
    m_Slots.clear();

    // 先依你圖片的六角盤做近似中心點
    // 座標原點以畫面中心為 0,0
    // 你之後只要微調這些數字，就能完全對齊圖片

    const std::vector<std::vector<glm::vec2>> rows = {
        { {-96, 150}, {-32, 150}, { 32, 150}, { 96, 150} },
        { {-128,  94}, {-64,  94}, {  0,  94}, { 64,  94}, {128,  94} },
        { {-160,  38}, {-96,  38}, {-32,  38}, { 32,  38}, { 96,  38}, {160,  38} },
        { {-160, -18}, {-96, -18}, {-32, -18}, { 32, -18}, { 96, -18}, {160, -18} },
        { {-160, -74}, {-96, -74}, {-32, -74}, { 32, -74}, { 96, -74}, {160, -74} },
        { {-128,-130}, {-64,-130}, {  0,-130}, { 64,-130}, {128,-130} },
        { {-96,-186}, {-32,-186}, { 32,-186}, { 96,-186} },
        { {  0,-242} }
    };

    int id = 0;
    for (const auto& row : rows) {
        for (const auto& pos : row) {
            Slot slot;
            slot.id = id++;
            slot.position = pos;
            slot.radius = 28.0f;
            m_Slots.push_back(slot);
        }
    }
}

const std::vector<StageObject::Slot>& StageObject::GetSlots() const {
    return m_Slots;
}