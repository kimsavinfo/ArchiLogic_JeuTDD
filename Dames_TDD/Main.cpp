#include <iostream>
using namespace std;

#include "Dames.h"

int main()
{
	Dames * dames = new Dames();
	dames->jouer();
	
	string exit = "\n\n\n Inserer un caractere pour quitter : ";
	cout << exit;
	cin >> exit;

	return 0;
}