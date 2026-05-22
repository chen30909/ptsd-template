#ifndef STAGE_CONFIG_HPP
#define STAGE_CONFIG_HPP

#include <glm/vec2.hpp>
#include <string>

struct StageConfig {
    int id;
    int boardSize;
    glm::vec2 mapPosition;
    glm::vec2 goalPosition;
    glm::vec2 hudPosition;
    std::string backgroundImage;
    std::string goalImage;
    std::string stageButtonImage;
    std::string clearButtonImage;
    std::string currentButtonImage;
    std::string goalDescription;
    int goalValue;
    int moveLimit;
    bool hasBoard;
};

const StageConfig& GetStageConfig(int stage);
bool IsPlayableStage(int stage);
int GetPlayableStageCount();
bool HasStageBoard(int stage);

#endif
