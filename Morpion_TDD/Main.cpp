#include <iostream>
using namespace std;

#include "Morpion.h"

int main()
{
	Morpion * morpion = new Morpion();
	morpion->afficherTitre();
	morpion->afficherJeu();
	morpion->jouer();

	string exit = "\n\n\n Ins�rer un caract�re pour quitter";
	cout << exit;
	cin >> exit;

	return 0;
}