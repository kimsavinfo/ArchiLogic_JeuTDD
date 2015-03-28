#include "stdafx.h"
#include "DriverGrilleMorpion.h"


DriverGrilleMorpion::DriverGrilleMorpion(int _nbLignes, int _nbColonnes) : DriverGrille(_nbLignes, _nbColonnes)
{
}

vector<ChoixCase *> DriverGrilleMorpion::getChoixCases()
{
	vector<ChoixCase *> choix;
	string legende;
	vector<long> casesVides = grille->getCasesVidesIds();

	for (int iCaseVide = 0; iCaseVide < casesVides.size(); iCaseVide++)
	{
		legende = to_string(choix.size() +1) + " - " + grille->getCaseLegende( casesVides.at(iCaseVide) ) ;
		choix.push_back( new ChoixCase( legende , casesVides.at(iCaseVide) ) );
	}

	return choix;
}

/* ======================================================= */
/* Déterminer si la partie est finie et s'il y a un gagnant ou églaité
/* Pour éviter de parcour toute la grille à chaque fois,
/* on ne regarde que les cases voisine qui sont susceptibles d'être impactées
/* ======================================================= */

void DriverGrilleMorpion::checkPartieFinie(long _idCase, vector<long> _pionsJoueur)
{
	map<string, int> coordonnees = grille->getCaseCoordonnees(_idCase);

	checkLigneGagnante(coordonnees["ligne"], _pionsJoueur);
	if(!partieFinie) checkColonneGagnante(coordonnees["colonne"], _pionsJoueur);
	if(!partieFinie) checkDiagonaleNOSEGagnante(_pionsJoueur);
	if(!partieFinie) checkDiagonaleNESOGagnante(_pionsJoueur);
	if(!partieFinie) checkEgalite();
}

void DriverGrilleMorpion::checkEgalite()
{
	if(grille->isGrilleRemplie())
	{
		setPartieFinieEgalite(true);
	}
}

void DriverGrilleMorpion::checkLigneGagnante(int _iLigne, vector<long> _pionsJoueur)
{
	int iColonne = 0;
	int nbColonnes = grille->getNbColonnes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCaseIdOccupant(_iLigne, iColonne);
		 
		if( find(_pionsJoueur.begin(), _pionsJoueur.end(), idOccupant) != _pionsJoueur.end() )
		{
			isPionAdverse = false;
			iColonne++;
		}
	}while(iColonne < nbColonnes && !isPionAdverse);

	if(iColonne == nbColonnes)
	{
		setPartieFinieEgalite(false);
	}
}

void DriverGrilleMorpion::checkColonneGagnante(int _iColonne, vector<long> _pionsJoueur)
{
	int iLigne = 0;
	int nbLignes = grille->getNbLignes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCaseIdOccupant(iLigne, _iColonne);

		if( find(_pionsJoueur.begin(), _pionsJoueur.end(), idOccupant) != _pionsJoueur.end() )
		{
			isPionAdverse = false;
			iLigne++;
		}
	}while(iLigne < nbLignes && !isPionAdverse);

	if(iLigne == nbLignes)
	{
		setPartieFinieEgalite(false);
	}
}

/**
*	Nord Ouest -> Sud Est
*/
void DriverGrilleMorpion::checkDiagonaleNOSEGagnante(vector<long> _pionsJoueur)
{
	int iColonne = 0;
	int iLigne = 0;
	int nbColonnes = grille->getNbColonnes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCaseIdOccupant(iLigne, iColonne);
		
		if( find(_pionsJoueur.begin(), _pionsJoueur.end(), idOccupant) != _pionsJoueur.end() )
		{
			isPionAdverse = false;
			iColonne++;
			iLigne++;
		}
	}while(iColonne < nbColonnes && !isPionAdverse);

	if(iColonne == nbColonnes)
	{
		setPartieFinieEgalite(false);
	}
}

/**
*	Nord Est -> Sud Ouest
*/
void DriverGrilleMorpion::checkDiagonaleNESOGagnante(vector<long> _pionsJoueur)
{
	int iColonne = grille->getNbColonnes() -1;
	int iLigne = 0;
	int nbLignes = grille->getNbLignes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCaseIdOccupant(iLigne, iColonne);
		
		if( find(_pionsJoueur.begin(), _pionsJoueur.end(), idOccupant) != _pionsJoueur.end() )
		{
			isPionAdverse = false;
			iColonne--;
			iLigne++;
		}
	}while(iLigne < nbLignes && !isPionAdverse);

	if(iLigne == nbLignes)
	{
		setPartieFinieEgalite(false);
	}
}

void DriverGrilleMorpion::setPartieFinieEgalite(bool _egalite)
{
	partieFinie = true;
	egalite = _egalite;
}

DriverGrilleMorpion::~DriverGrilleMorpion(void)
{
}
