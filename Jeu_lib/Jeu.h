#include <vector>
#include <string> 
#include <iostream>
using namespace std;

#include "Joueur.h"

class Jeu
{
	public:
		Jeu(void);
		~Jeu(void);

		virtual void afficherTitre();

	protected:
		int nbColonnes;
		int nbLignes;
		int nbJoueurs;
		int nbPionsParJoueur;
		int iTour;

	private:
		virtual void creerJoueurs();
};

