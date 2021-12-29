// par Renel Lherisson
#pragma once
#include <string>
#include "case.h"

class Connexion {
public:
	Connexion(Case* caseOne, Case* caseTwo, std::string positionOneVsTwo) {
		caseOne->setDirectionFromMe(caseTwo, positionOneVsTwo);
	}
};
