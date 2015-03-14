#include "stdafx.h"
#include "Jeu.h"

Jeu::Jeu(void)
{
	nbColonnes = 0;
	nbLignes = 0;
	nbJoueurs = 0;
	nbPionsParJoueur = 0;
	iTour = 0;
}

void Jeu::afficherTitre()
{
}

void Jeu::creerJoueurs()
{
}

Jeu::~Jeu(void)
{
	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		delete joueurs.at(iJoueur);
	}
}
