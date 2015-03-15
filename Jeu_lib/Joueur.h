#pragma once

#include <map>
#include <string>
using namespace std; 

class Joueur
{
	public:
		Joueur(string _nom, string _couleurHex);
		~Joueur(void);
		
		string getNom();

	protected:
		string nom;
		string couleurHex;
		
};

