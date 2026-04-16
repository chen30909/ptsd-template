#include "App.hpp"
#include "Global.hpp"
#include "Util/Keycode.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>
#include <vector>

using namespace std;

void DebugModeOfAppearance(const std::vector<std::shared_ptr<GameCharacter>>& objectArray, int size) {
    for (int i = 1; i < size + 1; ++i) {
        std::cout << "Pos number: " << objectArray.at(i)->GetInformationPosNumber()
                  << " Appear Bool: " << objectArray.at(i)->GetAppearBool() << std::endl;
    }
}

void DebugModeOfPosition(std::vector<std::shared_ptr<GameCharacter>>& objectArray, int option) {
    objectArray.at(option)->Appear();
    objectArray.at(option)->DebugMode(2.5);
}

void DebugModeCancel(std::vector<std::shared_ptr<GameCharacter>>& objectArray, int option) {
    objectArray.at(option)->DisAppear();
    std::cout << "x : " << objectArray.at(option)->GetPosition().x
              << " y : " << objectArray.at(option)->GetPosition().y << "\n";
}

void DebugModeShowMapObject(const std::vector<std::shared_ptr<GameCharacter>>& objectArray, int size) {
    for (int i = 1; i < size + 1; ++i) {
        cout << "Pos number: " << objectArray.at(i)->GetInformationPosNumber()
             << " Appear Bool: " << objectArray.at(i)->GetAppearBool() << endl;
    }
}