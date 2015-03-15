#pragma once

#include "Jeu.h"
#include "JoueurDames.h"
#include "ControleurGrilleDames.h"

class Dames : public Jeu
{
	public:
		Dames();
		~Dames(void);

		void afficherTitre();
		void afficherJeu();

	private :
		vector<JoueurDames*> joueurs;
		ControleurGrilleDames * controleur;

		void creerJoueurs();
		map<int, map<int, string>> construireRepresentation();
		void insererLigneLegendeColonnes(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne);
		void insererLigneVide(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne);
		void insererLignePleine(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne);
		void initGrillePionsBlancs();
		void initGrillePionsNoirs();

		map<long, PionDames*> getJoueursPions();
};

