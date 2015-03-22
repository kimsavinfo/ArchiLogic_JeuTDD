#pragma once

#include "Jeu.h"
#include "DriverGrilleMorpion.h"
#include "JoueurMorpion.h"

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
		vector<JoueurMorpion *> joueurs;

		void ajouterJoueur(string _nom, string _formePions);
		void afficherJoueurs();
};
