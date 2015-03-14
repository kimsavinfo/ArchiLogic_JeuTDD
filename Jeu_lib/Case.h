#pragma once

#include <iostream>
using namespace std;

class Case
{
	public:
		Case(string _legende) ;
		~Case(void);

		int getLargeur();
		bool isVide();

		long getId();
		string getLegende();
		int getIdOccupant();
		void setIdOccupant(long _idOccupant);
		string afficher();

	private:
		long idCase;
		string legende;
		long idOccupant;
};