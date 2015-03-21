#include "stdafx.h"
#include "Morpion.h"


Morpion::Morpion(void) : Jeu()
{
	driverGrille = new DriverGrilleMorpion(3, 3);
}

void Morpion::jouer()
{
	afficherTitre();
	afficherJeu();
}

/** ============================================================================================== */
/**	Affichage */
/** ============================================================================================== */

void Morpion::afficherTitre()
{
	cout << "========================" << endl;
	cout << "\tTic Tac Toe" << endl;
	cout << "========================" << endl;
}


void Morpion::afficherJeu()
{
	vector< vector<string> > affichage = creerAffichage();

	for(int iLig = 0; iLig < affichage.size(); iLig++)
    {
		for(int iCol = 0; iCol < affichage[iLig].size(); iCol++)
        {
			cout << affichage[iLig][iCol];
		}
		cout << endl;
	}
}


vector< vector<string> > Morpion::creerAffichage()
{ 
	Grille * grille = driverGrille->getGrille();
	int nbLignesAffichage = calculerNbLignesAffichage(grille);
	int nbColonnesAffichage = calculeNbColonnesAffichage(grille);
	vector< vector<string> > affichage = this->initAffichage(nbLignesAffichage, nbColonnesAffichage);
	
	for(int iLigneGrille = 0; iLigneGrille < grille->getNbLignes(); iLigneGrille++ )
	{
		for(int iColonneGrille = 0; iColonneGrille < grille->getNbColonnes(); iColonneGrille++ )
		{
			affichage[iLigneGrille * 2 + 2][iColonneGrille + 3] =  grille->getCase(iLigneGrille, iColonneGrille)->getRepresentation();
		}
	}


	return affichage;
}


int Morpion::calculerNbLignesAffichage(Grille * _grille)
{
	// +1 pour la ligne pour les légendes des colonnes
	// +1 pour la ligne entre les légendes et la grille
	// *2 pour la ligne pleine de séparation à chaque ligne de la grille
	return _grille->getNbLignes() * 2 + 2;
}

int Morpion::calculeNbColonnesAffichage(Grille * _grille)
{
	// +1 pour la légende
	// +1 pour la séparation
	// +1 pour le trait de séparation
	return _grille->getNbColonnes() + 3;
}

Morpion::~Morpion(void)
{
	delete driverGrille;
}
