// par Renel Lherisson
#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <cstring>

#include "case.h"
#include "connection.h"

class WorldMap {
public:
	WorldMap() = default;
	~WorldMap() = default;
	// To add a new case to the world map
	void addNewCase(Case newCase);
	// To set a new connexion between two cases already added to the world map
	// CaseTwo is at the position of caseOne
	void linkNewObject(std::string caseName, std::vector<Object> objectList);
	void setNewConnexion(Case& caseOne, Case& caseTwo, std::string position);
	// To navigate to the direction (ex. North) of aCase
	Case* navigateToNextCase(Case* aCase, std::string Direction);
	Case* searchCase(std::string aCase);
private:
	std::string switchOrientation(std::string direction); // to create complete connexion between two cases
	std::unordered_map<std::string, std::string> fourOrientations_{
		{"N", "North"},
		{"S", "South"},
		{"W", "West"},
		{"E", "East"} };
	std::unordered_map<std::string, std::unique_ptr<Case>> allCases_;
	friend class Connexion;
};