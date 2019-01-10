#include "StateManager.h"

unsigned int StateManager::Score = 0;

bool StateManager::NewScene = false;
std::string StateManager::SceneName;

int StateManager::Difficulty = 1;

int StateManager::KeyReturn = 0;

bool StateManager::LockInput = false;