#include <iostream>
using namespace std;

#include "Morpion.h"

int main()
{
	string yorn = "Y";

	Morpion * morpion = new Morpion();
	morpion->afficherTitre();
	morpion->afficherJeu();
	
	do
	{
		morpion->jouer();

		cout << "\n Rejouer ? (n/N pour quitter) : ";
		cin >> yorn;
	}while(yorn != "n" && yorn != "N");


	delete morpion;
	return 0;
}