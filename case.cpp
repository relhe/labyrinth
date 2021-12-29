// par Renel Lherisson
#include "case.h"

Case::Case(std::string name, std::string description) :
	name_(name),
	description_(description) {
	directionFromMe_ = {
		{"N", nullptr},
		{"S", nullptr},
		{"W", nullptr},
		{"E", nullptr}
	};
}

void Case::setDirectionFromMe(Case* otherCase, std::string positionFromMe) {
	if (directionFromMe_[positionFromMe] == nullptr && positionFromMe.size() !=0)
		directionFromMe_[positionFromMe] = otherCase;
	else return;
}

void Case::setObjects(Object& anObject) {
	auto myObject = std::make_shared<Object>(anObject);
	if (myObject != nullptr)
		objects_.push_back(std::move(myObject));
}

Object* Case::getObject(const std::string& someString,int fromPosition) const {
	auto end = objects_.end();
	for (auto it = objects_.begin(); it != end; ++it) {
		bool isIn = (*it)->IdObject(someString, fromPosition);
		if (isIn)
			return (*it).get();
	}
	return nullptr;
}

void Case::lookObject(std::string& someString, int position) {
	Object* myObject = getObject(someString, position);
	if (myObject != nullptr)
		std::cout << myObject->getDescription();
	else
		std::cout << "Can't find this Object!";
}

void Case::print(std::ostream& os) {
	os << "-- " + name_ + " --\n";
	os << description_ ;
	if (objects_.size() > 0) {
		os << "\nYou notice:";
		for (auto&& y : objects_)
			os << "\n    " + y->getName();
	}
	for (auto&& [x,y]:directionFromMe_) {
		if (x == "N" && y != nullptr)
			os <<"\n" + y->getName() + " is in the north (N)";
		else if (x == "S" && y != nullptr)
			os << "\n" + y->getName() + " is in the south (S)";
		else if (x == "W" && y != nullptr)
			os << "\n" + y->getName() + " is in the west (W)";
		else if (x == "E" && y != nullptr)
			os << "\n" + y->getName() + " is in the east (E)";
	}
}
