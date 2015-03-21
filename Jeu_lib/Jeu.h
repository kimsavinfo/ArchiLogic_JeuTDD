#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Jeu
{
	public:
		Jeu(void);
		~Jeu(void);

		virtual void afficherTitre();
		virtual void afficherJeu();
		virtual void jouer();

	protected:
		int nbLignesHeader;

		virtual vector< vector<string> > creerAffichage();
		vector< vector<string> > initAffichage(int _nbLignes, int _nbColonnes);

	private:
		string espaceVide;

		void setLegendeColonnes(vector< vector<string> > &_affichage);
		void setLigneVide(vector< vector<string> > &_affichage, int _iLigne);
		void setLignePleine(vector< vector<string> > &_affichage, int _iLigne);
};

