#pragma once

#include "Jeu.h"
#include "DriverGrilleMorpion.h"
#include "JoueurMorpion.h"

class Morpion : public Jeu
{
	public:
		Morpion(void);
		~Morpion(void);

		virtual void jouer();

	protected:
		virtual void afficherTitre();
		virtual void afficherJeu();
		virtual void afficherJoueurs();
		virtual vector< vector<string> > creerAffichage();

	private:
		DriverGrilleMorpion * driverGrille;
		vector<JoueurMorpion *> joueurs;
		int iTour;
		void ajouterJoueur(string _nom, string _formePions);
		
		long askJoueurQuelPionPoser();
		long askJoueurOuPoserPion();
		void poserPion();
		vector<long> getJoueursPionsIds();
};

