#pragma once

#include "Jeu.h"
#include "DriverGrilleMorpion.h"

class Morpion : public Jeu
{
	public:
		Morpion(void);
		~Morpion(void);

		virtual void afficherTitre();
		virtual void afficherJeu();
		virtual void jouer();

	protected:
		virtual vector< vector<string> > creerAffichage();

	private:
		DriverGrilleMorpion * driverGrille;

		int calculerNbLignesAffichage(Grille * _grille);
		int calculeNbColonnesAffichage(Grille * _grille);
};

