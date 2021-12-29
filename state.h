// par Renel Lherisson
#pragma once
#include <string>
#include <cctype>
#include <memory>
#include <unordered_map>
#include <functional>

#include "worldMap.h"
#include "case.h"
#include "interactive.h"

class GameState {
public:
	GameState();
	~GameState() = default;
	Case* loading();
	void playing(Case* start);
private:
	std::unique_ptr<WorldMap> myMap_;
	std::unordered_map<std::string, std::function<Case*(WorldMap*, Case*, std::string)>> actionMap_;
};
