/************************************************************************************************************
*             Fichier source du Projet du cours INF1015                                                     *
*************************************************************************************************************
*\fichier main.cpp                                                                                          *
*\ modification dans le code source fourni Par Francois R.Boyer (code en commentaire fin du main.ccp)       *
* ***********************************************************************************************************
*\Auteurs : Renel Lherisson  et Jean-Christophe Pelletier                                                   *
*\date : 22 decembre 2021  , cree le 9 decembre 2021                                                        *
************************************************************************************************************/

#pragma region "Biblioth�ques"//{

#include "state.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <gsl/span>
#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>

//#if __has_include("gtest/gtest.h")
//#include "gtest/gtest.h"
//#endif

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette ent�te si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par d�faut.

	//cdbg.setTee(&clog);  // D�commenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du d�bogueur.

	// bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un r�sultat de test.
#endif
}

using namespace std;
using namespace std::literals;
using namespace iter;
using namespace gsl;

#pragma endregion//}

int main(int argc, char* argv[])
{
	initialiserBibliothequeCours(argc, argv);	
	
	//--------New Game SET UP ------//
	GameState myGame;               //
	auto start = myGame.loading();  //
	myGame.playing(start);          //
	//------------------------------//

	////? Tout a �t� mis dans le main, aucun orient�-objet.
	//cout << "Ceci est mon super jeu mal programm�.\n\n";

	////? Tout peux modifier ces variables (aucune encapsulation).
	//int salle = 0;  //? Quelle valeur est quelle salle?
	//string commande;
	//bool look = true;  //? La logique pour fonctionnalit� look n'est pas bien s�par�e/regroup�e (voir les plusieurs modifications et utilisations de look partout dans le code).

	//while (true) {
	//	switch (salle) {  //? Un gros switch/case, imaginez s'il y avait des centaines de salles...
	//	case 0:
	//		if (look) //? Aucune s�paration de la logique par rapport au contenu du jeu.
	//			cout << "Vous �tes dans l'entr�e. Il y a un tapis sur le sol.\n"
	//			"Couloir est au nord (N)\n"  //? Les textes des directions sont "hard-cod�es", on peut se tromper et il faut modifier plusieurs endroits pour ajouter un lien.
	//			"Salon est � l'est (E)\n";  //? Aussi comment on fait pour pouvoir ajouter des liens pendant le jeu (demand� au livrable 2)?
	//		look = false;
	//		cout << "> ";
	//		cin >> commande;
	//		if (commande.size() == 1) {
	//			switch (commande[0]) {
	//			case 'N': salle = 2; look = true; break;  //? On remet look = true dans chaque direction, c'est clairement de la duplication de code; la logique qui fait l'affichage lorsqu'on entre dans une salle devrait �tre � un seul endroit dans le code.
	//			case 'E': salle = 1; look = true; break;
	//			default: cout << "Ne peut pas aller l�\n";
	//			}
	//		}
	//		else if (commande == "look") look = true;
	//		else cout << "Je ne sais pas �a\n";
	//		break;

	//		//? Clairement de la duplication de code dans chaque 'case'.
	//	case 1:
	//		if (look)
	//			cout << "Vous �tes dans le salon.\n"
	//			"Entr�e est � l'ouest (W)\n";
	//		look = false;
	//		cout << "> ";
	//		cin >> commande;
	//		if (commande.size() == 1) {
	//			switch (commande[0]) {
	//			case 'W': salle = 0; look = true; break;
	//			default: cout << "Ne peut pas aller l�\n";
	//			}
	//		}
	//		else if (commande == "look") look = true;  //? Imaginez si on voulair ajouter d'autres commandes...
	//		else cout << "Je ne sais pas �a\n";
	//		break;

	//	case 2:
	//		if (look)
	//			cout << "Vous �tes dans le couloir.\n"
	//			"Cuisine est au nord (N)\n"
	//			"Petite chambre est � l'ouest (W)\n"
	//			"Entr�e est au sud (S)\n";
	//		look = false;
	//		cout << "> ";
	//		cin >> commande;
	//		if (commande.size() == 1) {
	//			switch (commande[0]) {
	//			case 'N': salle = 4; look = true; break;
	//			case 'W': salle = 3; look = true; break;
	//			case 'S': salle = 0; look = true; break;
	//			default: cout << "Ne peut pas aller l�\n";
	//			}
	//		}
	//		else if (commande == "look") look = true;
	//		else cout << "Je ne sais pas �a\n";
	//		break;

	//	case 3:
	//		if (look)
	//			cout << "Vous �tes dans une petite chambre. Elle n'a rien de sp�cial autre que d'�tre petite.\n"
	//			"Couloir est � l'est (E)\n";
	//		look = false;
	//		cout << "> ";
	//		cin >> commande;
	//		if (commande.size() == 1) {
	//			switch (commande[0]) {
	//			case 'E': salle = 2; look = true; break;
	//			default: cout << "Ne peut pas aller l�\n";
	//			}
	//		}
	//		else if (commande == "look") look = true;
	//		else cout << "Je ne sais pas �a\n";
	//		break;

	//	case 4:
	//		if (look)
	//			cout << "Vous �tes dans la cuisine. Elle est tr�s jaune 'beurre' comme la mode d'une certaine �poque.\n"
	//			"Couloir est au sud (S)\n";
	//		look = false;
	//		cout << "> ";
	//		cin >> commande;
	//		if (commande.size() == 1) {
	//			switch (commande[0]) {
	//			case 'S': salle = 2; look = true; break;
	//			default: cout << "Ne peut pas aller l�\n";
	//			}
	//		}
	//		else if (commande == "look") look = true;
	//		else cout << "Je ne sais pas �a\n";
	//		break;
	//	}
	//}
}