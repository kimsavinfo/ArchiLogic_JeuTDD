#include "stdafx.h"
#include "Morpion.h"


Morpion::Morpion(void) : Jeu()
{
	driverGrille = new DriverGrilleMorpion(3, 3);

	ajouterJoueur("Alice", "X");
	ajouterJoueur("Bob", "O");
}

void Morpion::jouer()
{
	afficherTitre();
	afficherJoueurs();
	afficherJeu();
}

void Morpion::ajouterJoueur(string _nom, string _formePions)
{
	joueurs.push_back( new JoueurMorpion(_nom, _formePions) );
}

void Morpion::afficherJoueurs()
{
	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		cout << joueurs[iJoueur]->getNom() << " joue avec les pions " << joueurs[iJoueur]->getForme() << endl ;
	}
	cout << endl;
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

	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		delete joueurs.at(iJoueur);
	}
}
