#pragma once

#include <map>
#include <string>
using namespace std; 

#include "Pion.h"

class Joueur
{
	public:
		Joueur(string _nom, string _couleurHex);
		~Joueur(void);
		
		void attribuerPions(int _nbPions, string _formePion);
		string getNom();
		map<long, Pion*> getPions();
		Pion* getNextPionNonSurGrille();
		void poserPion(long _idPion);

	private:
		string nom;
		string couleurHex;
		map<long, Pion*> pions;
};

