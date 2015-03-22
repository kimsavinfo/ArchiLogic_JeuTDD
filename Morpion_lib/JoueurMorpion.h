#pragma once

#include <map>

#include "Joueur.h"
#include "FactoryPionMorpion.h"

class JoueurMorpion : public Joueur
{
	public:
		JoueurMorpion(string _nom, string _forme);
		~JoueurMorpion(void);

		string getFormePions();
		PionMorpion * getPionAPoser();
		void poserPion(long _idPion);

		map<long, PionMorpion*> getPions();

	private:
		map<long, PionMorpion*> pions;

		void creerPions(string _forme);
};

