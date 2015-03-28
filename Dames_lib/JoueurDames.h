#pragma once

#include <map>
#include <vector>

#include "Joueur.h"
#include "FactoryPionDames.h"

class JoueurDames : public Joueur
{
	public:
		JoueurDames(string _nom, string _couleur, int _sensVertical);
		~JoueurDames(void);

		string getCouleurPions();
		vector<long> getPionsIds();
		bool isPionAuJoueur(long _idPion);
		string getPionRepresentation(long _idPion);
		int getSensVertical();

	private:
		map<long, PionDames*> pions;
		void creerPions(string _couleur);
		int sensVertical;
};

