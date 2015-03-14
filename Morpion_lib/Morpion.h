#pragma once

#include "Jeu.h"
#include "Joueur.h"
#include "ControleurGrilleMorpion.h"

class Morpion : public Jeu
{
	public:
		Morpion();
		~Morpion(void);

		void afficherTitre();
		void afficherJeu();
		void jouer();

	private:
		ControleurGrilleMorpion * controleur;

		void creerJoueurs();
		map<int, map<int, string>> construireRepresentation();
		void insererLigneLegendeColonnes(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne);
		void insererLigneVide(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne);
		void insererLignePleine(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne);
		long askJoueurQuelPionPoser();
		long askJoueurOuPoserPion();
		void poserPion();
		

		map<long, Pion*> getJoueursPions();
};

