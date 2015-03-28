#pragma once

#include <map>
#include <vector>

#include "Joueur.h"
#include "FactoryPionMorpion.h"

class JoueurMorpion : public Joueur
{
	public:
		JoueurMorpion(string _nom, string _forme);
		~JoueurMorpion(void);

		string getFormePions();
		long getIdPionAPoser();
		bool isPionAuJoueur(long _idPion);
		vector<long> getPionsIds();
		void poserPion(long _idPion);


	private:
		map<long, PionMorpion*> pions;

		void creerPions(string _forme);
};

