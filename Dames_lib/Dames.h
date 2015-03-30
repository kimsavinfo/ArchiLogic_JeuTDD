#pragma once

#include "Jeu.h"
#include "DriverGrilleDames.h"
#include "JoueurDames.h"

class Dames : public Jeu
{
	public:
		Dames(void);
		~Dames(void);

		virtual void jouer();

	protected:
		virtual void afficherTitre();
		virtual void afficherJeu();
		virtual void afficherJoueurs();
		virtual vector< vector<string> > creerAffichage();

	private:
		DriverGrilleDames * driverGrille;
		vector<JoueurDames *> joueurs;

		void ajouterJoueur(string _nom, string _couleur, int _sensVertical);
		void initJeu();
		string getPionRepresentation(long _idPion);
		ChoixPion * askQuelPionDeplacer();
		ChoixDeplacement * askOuDeplacerPion(ChoixPion * _pionADeplacer);
		void mangerPions(vector<long> _pionsManges);
};

