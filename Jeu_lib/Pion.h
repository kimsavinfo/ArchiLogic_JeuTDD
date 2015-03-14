#pragma once

#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class Pion
{
	public:
		Pion(string _forme, string _couleurHex);
		~Pion(void);
		
		long getId();
		string afficher();
		bool isSurGrille();
		void setSurGrille(bool _surGrille);

	private:
		long idPion;
		string forme;
		string couleurHex;
		bool surGrille;
};

