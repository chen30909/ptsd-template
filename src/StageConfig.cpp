#include "StageConfig.hpp"

#include "Global.hpp"

#include <array>
#include <stdexcept>

namespace {
const std::array<StageConfig, 11> kStageConfigs = {{
    {0, 0, {-100000.0f, -100000.0f}, {-100000.0f, -100000.0f}, {-100000.0f, -100000.0f}, "homePage.png", "", "", "", "", "", 0, 0, false},
    {1, 37, {-64.5f, 87.5f}, {-100.0f, 225.0f}, {5.0f, 185.0f}, "first.png", BROWN_NORMAL_OBJECT, LEVEL_ONE_IMAGE, LEVEL_ONE_CLEAR, LEVEL_ONE_CURRENT, "Remove Brown Object", 15, 30, true},
    {2, 45, {0.0f, 87.5f}, {-100.0f, 255.5f}, {5.0f, 215.5f}, "second.png", BROWN_NORMAL_OBJECT, LEVEL_TWO_IMAGE, LEVEL_TWO_CLEAR, LEVEL_TWO_CURRENT, "Remove Brown Object", 15, 30, true},
    {3, 47, {64.5f, 87.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "third.png", REACH_IMAGE, LEVEL_THREE_IMAGE, LEVEL_THREE_CLEAR, LEVEL_THREE_CURRENT, "Reach Score", 140, 40, true},
    {4, 64, {64.5f, 37.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "fourth.png", REACH_IMAGE, LEVEL_FOUR_IMAGE, LEVEL_FOUR_CLEAR, LEVEL_FOUR_CURRENT, "Reach Score", 160, 40, true},
    {5, 39, {0.0f, 37.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "fifth.png", COOKIE_ONE_IMAGE, LEVEL_FIVE_IMAGE, LEVEL_FIVE_CLEAR, LEVEL_FIVE_CURRENT, "Remove Cookies", 26, 25, true},
    {6, 72, {-64.5f, 37.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "sixth.png", COOKIE_ONE_IMAGE, LEVEL_SIX_IMAGE, LEVEL_SIX_CLEAR, LEVEL_SIX_CURRENT, "Remove Cookies", 35, 40, true},
    {7, 60, {-64.5f, -17.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "seventh.png", COOKIE_ONE_IMAGE, LEVEL_SEVEN_IMAGE, LEVEL_SEVEN_CLEAR, LEVEL_SEVEN_CURRENT, "Remove Cookies", 22, 40, true},
    {8, 70, {0.0f, -17.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "eighth.png", BLUE_FLOWER_OBJECT, LEVEL_EIGHT_IMAGE, LEVEL_EIGHT_CLEAR, LEVEL_EIGHT_CURRENT, "Create And Remove Any Flowers", 8, 50, true},
    {9, 43, {64.5f, -17.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "ninth.png", BLUE_STRIPE_OBJECT, LEVEL_NINE_IMAGE, LEVEL_NINE_CLEAR, LEVEL_NINE_CURRENT, "Create And Remove Any Stripes", 10, 40, true},
    {10, 73, {64.5f, -67.5f}, {-100.0f, 235.0f}, {5.0f, 185.0f}, "tenth.png", BLUE_STRIPE_OBJECT, LEVEL_TEN_IMAGE, LEVEL_TEN_CLEAR, LEVEL_TEN_CURRENT, "Create And Remove Any Stripes", 10, 40, true},
}};
}

const StageConfig& GetStageConfig(int stage) {
    if (stage < 0 || stage >= static_cast<int>(kStageConfigs.size())) {
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
