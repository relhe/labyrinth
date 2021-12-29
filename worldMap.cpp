// par Renel Lherisson
#include "WorldMap.h"

void WorldMap::addNewCase(Case newCase) {
	std::unique_ptr<Case> myNewCase = std::make_unique<Case>(newCase);
	allCases_[myNewCase->getName()] = std::move(myNewCase);
}

void WorldMap::setNewConnexion(Case& caseOne, Case& caseTwo, std::string position) {
	// Verify that both cases are already saved before connecting
	auto last = allCases_.end();
	auto caseOneIn = allCases_.find(caseOne.getName());
	auto caseTwoIn = allCases_.find(caseTwo.getName());
	if (caseOneIn != last && caseTwoIn != last) {
		Connexion(allCases_[caseOne.getName()].get(), allCases_[caseTwo.getName()].get(), position);
		Connexion(allCases_[caseTwo.getName()].get(), allCases_[caseOne.getName()].get(), switchOrientation(position));
	}
}

Case* WorldMap::navigateToNextCase(Case* aCase, std::string toDirection) {
	if (aCase->findAtDirection(toDirection) == nullptr) {
		std::cout << "You cannot go there.";
		return aCase;
	}
	else {
		std::cout << "Going " + fourOrientations_[toDirection] + "\n";
		std::cout << "\n";
		Case* nextCase = aCase->findAtDirection(toDirection);
		nextCase->print(std::cout);
		return nextCase;
	}
}

Case* WorldMap::searchCase(std::string aCase) {
	auto caseIn = allCases_.find(aCase);
	if (caseIn != allCases_.end())
		return allCases_[aCase].get();
	return nullptr;
}

std::string WorldMap::switchOrientation(std::string direction) {
	switch (direction[0]) {
	case 'N': return "S";
	case 'S': return "N";
	case 'E': return "W";
	case 'W': return "E";
	default: return"";
	}
}

void WorldMap::linkNewObject(std::string caseName, std::vector<Object> objectList) {
	auto caseIn = allCases_.find(caseName);
	if (caseIn != allCases_.end()) {
		for (auto& obj : objectList) {
			(*caseIn).second->setObjects(obj);
		}
	}
}
