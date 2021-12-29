#include "state.h"

GameState::GameState() {
	myMap_ = std::make_unique<WorldMap>();
	// ------------------------- set up game commands --------------------------------------------------------------------------------------
	actionMap_["look"] = [](WorldMap* map, Case* aCase, std::string entry) {
		aCase->print(std::cout);
		return aCase;
	};

	actionMap_["use"] = [](WorldMap* map, Case* aCase, std::string entry) {
		std::cout << "The use command should be called with an object name or a keyword!";
		return aCase;
	};

	actionMap_["useLook"] = [](WorldMap* map, Case* aCase, std::string entry) {
		if (entry.substr(0, 4) == "look")   //look for object
			aCase->lookObject(entry, 3);
		else if (entry.substr(0, 3) == "use") {  //use object
			Object* myObject = aCase->getObject(entry, 3);
			if (myObject != nullptr) {
				if (myObject->getName() == "A red Button")
					map->setNewConnexion(*(map->searchCase("main hallway")), *(map->searchCase("Room R")), "E");
				std::cout << myObject->useMe();
			}
			else
				std::cout << "Can't find this Object!";
		}
		else
			std::cout << "I don't know that.";
		return aCase;
	};

	//--------------------------------------- orientation commands ---------------------------------------------------------------------------
	actionMap_["direction"] = [](WorldMap* map, Case* aCase, std::string entry) {
		if (entry == "N" || entry == "S" || entry == "E" || entry == "W") {
			Case* newCase = map->navigateToNextCase(aCase, entry);
			return newCase;
		}
		else
			std::cout<< "I don't know that.";
		return aCase;
	};
	
	//----------------------------------------------- game quitting commands -----------------------------------------------------------------
	actionMap_["exit"] = [](WorldMap* map, Case* aCase, std::string entry) {
		std::cout << "Thanks for playing!\n";
		return nullptr;
	};
	//------------------------------------ end setting up game commands ---------------------------------------------------------------------
}

Case* GameState::loading() {
	// Manually loaded data 
	//--------------------------- creation and map case loading ------------------------------------------------------------------------------
	myMap_->addNewCase({ "entrance", "This is the entrance. There is a carpet on the floor." });
	myMap_->addNewCase({ "living room", "This is the living room. There is a big couch and a 65\" flat screen TV." });
	myMap_->addNewCase({ "main hallway", "This is the main hallway. There is a bunch of boxes against the wall." });
	myMap_->addNewCase({ "small room", "It has nothing special but small." });
	myMap_->addNewCase({ "kitchen", "It is very yellow 'butter' like the fashion of a certain period." });
	myMap_->addNewCase({ "Room R", "This is a hidden room in the house. Access was granted by pressing the red button." });
	//--------------------------- map initial case linking  ------------- --------------------------------------------------------------------
	myMap_->setNewConnexion(*(myMap_->searchCase("entrance")), *(myMap_->searchCase("main hallway")), "N");
	myMap_->setNewConnexion(*(myMap_->searchCase("entrance")), *(myMap_->searchCase("living room")), "E");
	myMap_->setNewConnexion(*(myMap_->searchCase("main hallway")), *(myMap_->searchCase("small room")), "W");
	myMap_->setNewConnexion(*(myMap_->searchCase("main hallway")), *(myMap_->searchCase("kitchen")), "N");
	// ---------------------------------- Add object to existing cases -----------------------------------------------------------------------
	// ----- objects are created outside to Worldmap to facilitate association to other room if necessary ------------------------------------
	Object redButton{ "A red Button", "You can access Room R by using the Red Button!" };
	Object piano{ "A cheap electric piano", "This is an old entry-level Yamaha with 61 keys. It looks like any cheap stuff from late 90's" };
	Object lightSwitch{ "A light switch", "There is ON and OFF written in black on the light switch" };
	Object greenKey{ "A green key", "It looks like the green key is made of silver" };
	Object pairOfMenShoes{ "A pair of men shoes", "These shoes are made of black leather" };
	Object smallBed{ "A very tiny Bed", "This small bed is 38 inches by 75 inches." };

	redButton.addKeyWords({ "red", "red button", "button" });
	piano.addKeyWords({ "piano", "electric piano", "cheap electric piano", "cheap" });
	lightSwitch.addKeyWords({ "switch", "light", "light switch", "light on", "light off" });
	greenKey.addKeyWords({ "green", "key", "greenKey" });
	pairOfMenShoes.addKeyWords({ "pair", "shoes", "men shoes", "men", "pair of men shoes", "shoe"});
	smallBed.addKeyWords({ "very", "tiny", "bed"});
		
    // -----------------------------------------  filling some utilisations ------------------------------------------------------------------
	redButton.addNewUtilisation("Main hallway is now connected to Room R. Access is granted!"); 
	for (auto i : {
		"You play some chords on the piano. It does sound very well.",
		"You are playing G chord follewed by E minor and C!",
		"You are playing a F chord",
		"A green key falls off while you  play."})
	piano.addNewUtilisation(i);
	for (auto j : {
		"You've switched the light bulb to ON.",
		"You've switched the light bulb to OFF."})
	lightSwitch.addNewUtilisation(j);
	greenKey.addNewUtilisation("Your are using the green key to open the safe! This is it's only utility.");
	pairOfMenShoes.addNewUtilisation("You wear the shoes! You are about to go outside!");
	for (auto k : {
		"You sit down on the tiny bed.",
		"You lay down on the small bed." })
	smallBed.addNewUtilisation(k);


	myMap_->linkNewObject("entrance", { pairOfMenShoes });
	myMap_->linkNewObject("living room", { piano, redButton, greenKey });
	myMap_->linkNewObject("main hallway", { lightSwitch });
	myMap_->linkNewObject("small room", { smallBed });
	myMap_->linkNewObject("Room R", { lightSwitch, smallBed });
	// ---------------------------------- end of loading game data ----------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------------------------------
	return myMap_->searchCase("entrance");
}

void GameState::playing(Case* start) {
	//--------------------------------------  Game execution --------------------------------------------------------------------------------
	std::cout << ">>>>>>>>> INF1015 CONSOLE NAVIGATION 2021 <<<<<<<<<\n";
	std::cout << "> > > > >    GAME OF THE YEAR EDITION     < < < < <\n\n";
	start->print(std::cout);
	Case* playing = start;
	std::string search;
	std::string dir;
	do {
		//user entry
		std::cout << "\n\n> ";
		std::getline(std::cin, dir);
		search = dir;
		//entry preprocessing
		if (dir.size() == 1) {  // process lower case entry as upper one " n s w e --- N S W E "
			dir = char(std::toupper(dir[0]));
			search = "direction";
		}
		else if (dir.size() > 4)
			search = "useLook";
		//playing commands
		try {
			playing = actionMap_[search](myMap_.get(), playing, dir);
		}
		catch (...) {
				std::cout << "I don't know that.";
		}
	} while (playing != nullptr);
}
