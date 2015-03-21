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
	int nbLignes = grille->getNbLignes();
	int nbColonnes = grille->getNbColonnes();
	vector< vector<string> > affichage = this->initAffichage(nbLignes, nbColonnes);
	
	for(int iLigneGrille = 0; iLigneGrille < nbLignes; iLigneGrille++ )
	{
		for(int iColonneGrille = 0; iColonneGrille < nbColonnes; iColonneGrille++ )
		{
			affichage[iLigneGrille * 2 + nbLignesLegende][iColonneGrille + nbColonnesLegende] =  grille->getCase(iLigneGrille, iColonneGrille)->getRepresentation();
		}
	}

	return affichage;
}

Morpion::~Morpion(void)
{
	delete driverGrille;
}
