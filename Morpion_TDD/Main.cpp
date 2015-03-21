#include <iostream>
using namespace std;

#include "Morpion.h"

int main()
{
	Morpion * morpion = new Morpion();
	morpion->jouer();

	string exit = "\n\n\nInserer un caractere pour quitter : ";
	cout << exit;
	cin >> exit;

	return 0;
}