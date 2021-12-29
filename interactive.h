#pragma once
#include <string>
#include <vector>

class Object {
public:
	Object(std::string name, std::string description);
	~Object() = default;
	std::string getName() const { return name_; }
	std::string getDescription() const { return description_; }
	void addKeyWords(std::vector<std::string> keyWords);
	void addNewUtilisation(std::string utilisation) { utilisationList_.push_back(utilisation); }
	bool IdObject(const std::string& input, int startingPoint);
	const std::string useMe();
	void addObjectInside(Object* anObject);
private:
	std::string name_;
	std::string description_;
	std::vector<std::string> keyWords_;
	std::vector<std::string> utilisationList_;
	std::vector<Object*> objectsInside_;  //for object that contents other objects
	unsigned utilisationCounter_ = 0;
};