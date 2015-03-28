#pragma once

#include <map>
#include <vector>

#include "FactoryPionDames.h"

class JoueurDames
{
	public:
		JoueurDames(string _nom, string _couleur);
		~JoueurDames(void);

		string getCouleurPions();
		vector<long> getPionsIds();
		bool isPionAuJoueur(long _idPion);
		string getPionRepresentation(long _idPion);

	private:
			map<long, PionDames*> pions;
			void creerPions(string _couleur);
};

