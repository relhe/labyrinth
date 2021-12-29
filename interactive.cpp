#include "interactive.h"

Object::Object(std::string name, std::string description) :
	name_(name),
	description_(description) {
	keyWords_ = {};
	utilisationList_ = {};
}

void Object::addKeyWords(std::vector<std::string> keyWords) {
	for (auto word : keyWords)
		keyWords_.push_back(word);
}

bool Object::IdObject(const std::string& input, int startingPoint) {
	for (std::string keyWord : keyWords_) {
		auto it = input.find(keyWord, startingPoint);
		if (it != std::string::npos)
		    return true;
	}
	return false;
}

void Object::addObjectInside(Object* anObject) {
	if (anObject != nullptr)
		objectsInside_.push_back(anObject);
}

const std::string Object::useMe() {
	if (utilisationList_.size() == 1)
		return utilisationList_[utilisationCounter_];
	else if (utilisationList_.size() > 1) {
		if (utilisationCounter_ < utilisationList_.size()) {
			std::string useCase = utilisationList_[utilisationCounter_];
			++utilisationCounter_;
			return useCase;
		}
		else {
			utilisationCounter_ = 1;
			return utilisationList_[0];
		}
	}
	else
		return "This object has no specific utility. \n";
}