#include "StageConfig.hpp"

#include "Global.hpp"

#include <array>
#include <stdexcept>

namespace {
const std::array<StageConfig, 11> kStageConfigs = {{
    {0, 0, "homePage.png", "", false},
    {1, 37, "first.png", BROWN_NORMAL_OBJECT, true},
    {2, 0, "second.png", EMPTY_OBJECT, false},
    {3, 0, "third.png", EMPTY_OBJECT, false},
    {4, 0, "fourth.png", EMPTY_OBJECT, false},
    {5, 0, "fifth.png", EMPTY_OBJECT, false},
    {6, 0, "sixth.png", EMPTY_OBJECT, false},
    {7, 0, "seventh.png", EMPTY_OBJECT, false},
    {8, 0, "eighth.png", EMPTY_OBJECT, false},
    {9, 0, "ninth.png", EMPTY_OBJECT, false},
    {10, 0, "tenth.png", EMPTY_OBJECT, false},
}};
}

const StageConfig& GetStageConfig(int stage) {
    if (!IsPlayableStage(stage)) {
        throw std::out_of_range("Invalid stage id");
    }
    return kStageConfigs.at(static_cast<size_t>(stage));
}

bool IsPlayableStage(int stage) {
    return stage > 0 && stage < static_cast<int>(kStageConfigs.size());
}

int GetPlayableStageCount() {
    return static_cast<int>(kStageConfigs.size()) - 1;
}

bool HasStageBoard(int stage) {
    return IsPlayableStage(stage) && GetStageConfig(stage).hasBoard;
}
