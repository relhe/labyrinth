// par Renel Lherisson
#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <unordered_map>

#include "interactive.h"

class Case {
public:
	Case() = default;
	Case(std::string name, std::string description);
	Case(Case& otherCase):
		name_(otherCase.getName()),
		description_(otherCase.getDescription()){}
	~Case() = default;
	const std::string& getName() const {return name_;}
	void print(std::ostream& os);
	const std::string& getDescription() const { return description_; }
	Case* findAtDirection(std::string directionFromMe) { return directionFromMe_[directionFromMe]; }
	void setObjects(Object& anObject);
	void lookObject(std::string& someString, int position);
	Object* getObject(const std::string& someString, int fromPosition) const;
private:
	std::string name_;
	std::string description_;
	std::unordered_map<std::string, Case*> directionFromMe_;
	std::vector<std::shared_ptr<Object>> objects_;
	void setDirectionFromMe(Case* otherCase, std::string positionFromMe);
	friend class Connexion;
};
