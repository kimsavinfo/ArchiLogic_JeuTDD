#include "stdafx.h"
#include "ControleurGrilleMorpion.h"


ControleurGrilleMorpion::ControleurGrilleMorpion(int _nbColonnes, int _nbLignes) 
{
	grille = new Grille(_nbColonnes, _nbLignes);
	partieFinie = false;
	egalite = false;
}

map<int, map<int,  map<long, Case*>>> ControleurGrilleMorpion::getGrilleCases()
{
	return grille->getCases();
}

int ControleurGrilleMorpion::getGrilleLargeur()
{
	return grille->getLargeur();
}

vector<ChoixDeplacement*> ControleurGrilleMorpion::getChoix()
{
	vector<ChoixDeplacement*> choix;
	string legende;

	map<long, Case*> casesVides = grille->getCasesVides();
	for (auto const& caseVide: casesVides)
	{
		legende = to_string(choix.size() +1) + " - " + caseVide.second->getLegende();
		choix.push_back( new ChoixDeplacement( legende , caseVide.second->getId()) );
	}

	return choix;
}

void ControleurGrilleMorpion::poserPion(long _idPion, long _idCase)
{
	grille->poserPion(_idPion, _idCase);
}

/**
*	Pour �viter de parcour toute la grille � chaque fois,
*	on ne regarde que les cases voisine qui sont susceptibles d'�tre impact�es
*/
void ControleurGrilleMorpion::checkPartieFinie(long _idCase, map<long, Pion*> _pionsJoueur)
{
	map<string, int> coordonnees = grille->getCaseCoordonnees(_idCase);

	checkLigneGagnante(coordonnees["ligne"], _pionsJoueur);
	if(!partieFinie) checkColonneGagnante(coordonnees["colonne"], _pionsJoueur);
	if(!partieFinie) checkDiagonaleNOSEGagnante(_pionsJoueur);
	if(!partieFinie) checkDiagonaleNESOGagnante(_pionsJoueur);
	if(!partieFinie) checkEgalite();
}

void ControleurGrilleMorpion::checkEgalite()
{

	
	// setPartieFinieEgalite(true);
}

void ControleurGrilleMorpion::checkLigneGagnante(int _iLigne, map<long, Pion*> _pionsJoueur)
{
	int iColonne = 0;
	int nbColonnes = grille->getNbColonnes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCase(_iLigne, iColonne)->getIdOccupant();
		if( !(_pionsJoueur.find(idOccupant) == _pionsJoueur.end()) )
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

void ControleurGrilleMorpion::checkColonneGagnante(int _iColonne, map<long, Pion*> _pionsJoueur)
{
	int iLigne = 0;
	int nbLignes = grille->getNbLignes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCase(iLigne, _iColonne)->getIdOccupant();
		if( !(_pionsJoueur.find(idOccupant) == _pionsJoueur.end()) )
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
void ControleurGrilleMorpion::checkDiagonaleNOSEGagnante(map<long, Pion*> _pionsJoueur)
{
	int iColonne = 0;
	int iLigne = 0;
	int nbColonnes = grille->getNbColonnes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCase(iLigne, iColonne)->getIdOccupant();
		if( !(_pionsJoueur.find(idOccupant) == _pionsJoueur.end()) )
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
void ControleurGrilleMorpion::checkDiagonaleNESOGagnante(map<long, Pion*> _pionsJoueur)
{
	int iColonne = grille->getNbColonnes() -1;
	int iLigne = 0;
	int nbLignes = grille->getNbLignes();
	bool isPionAdverse = true;
	long idOccupant;

	do
	{
		isPionAdverse = true;

		idOccupant = grille->getCase(iLigne, iColonne)->getIdOccupant();
		if( !(_pionsJoueur.find(idOccupant) == _pionsJoueur.end()) )
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

void ControleurGrilleMorpion::setPartieFinieEgalite(bool _egalite)
{
	partieFinie = true;
	egalite = _egalite;
}

bool ControleurGrilleMorpion::isPartieFinie()
{
	return partieFinie;
}
bool ControleurGrilleMorpion::isEgalite()
{
	return egalite;
}

ControleurGrilleMorpion::~ControleurGrilleMorpion(void)
{
	delete grille;
}
