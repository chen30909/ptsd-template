#ifndef STAGE_CONFIG_HPP
#define STAGE_CONFIG_HPP

#include <string>

struct StageConfig {
    int id;
    int boardSize;
    std::string backgroundImage;
    std::string goalImage;
    bool hasBoard;
};

const StageConfig& GetStageConfig(int stage);
bool IsPlayableStage(int stage);
int GetPlayableStageCount();
bool HasStageBoard(int stage);

#endif