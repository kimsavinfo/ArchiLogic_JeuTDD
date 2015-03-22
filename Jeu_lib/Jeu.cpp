#include "stdafx.h"
#include "Jeu.h"


Jeu::Jeu(void)
{
	espaceVide = "    ";
	nbLignesLegende = 2; // Numobre de lignes pour les légendes
	nbColonnesLegende = 3; // Nombre de colonnes pour les légendes
}

void Jeu::jouer()
{
	cout << "Jouer";
}

void Jeu::afficherTitre()
{
	cout << "Titre du jeu";
}

void Jeu::afficherJeu()
{
	cout << "| |";
}

vector< vector<string> > Jeu::creerAffichage()
{
	return initAffichage(1,1);
}

vector< vector<string> > Jeu::initAffichage(int _nbLignes, int _nbColonnes)
{
	vector< vector<string> > affichage;
	int nbLignesTotal = calculerNbLignesAffichage(_nbLignes);
	int nbColonnesTotal = calculeNbColonnesAffichage(_nbColonnes);

	for (int iLigne = 0; iLigne < nbLignesTotal; iLigne++)
	{
		affichage.push_back( vector<string>() );

		for (int iColonne = 0; iColonne < nbColonnesTotal; iColonne++)
		{
			affichage[iLigne].push_back(espaceVide);

			if(iLigne > 1)
			{
				if(iColonne == 0)
				{
					affichage[iLigne][iColonne] = to_string(iLigne / 2);
				}
				else if(iColonne == nbColonnesLegende - 1)
				{
					affichage[iLigne][iColonne] = "|";
				}
			}
		}
		
		if(iLigne > 1 && iLigne % 2 == 1)
		{
			setLignePleine(affichage, iLigne);
		}
	}

	setLegendeColonnes(affichage);

	return affichage;
}

int Jeu::calculerNbLignesAffichage(int _nbLignesInit)
{
	// +1 pour la ligne pour les légendes des colonnes
	// +1 pour la ligne entre les légendes et la grille
	// *2 pour la ligne pleine de séparation à chaque ligne de la grille
	return _nbLignesInit * 2 + nbLignesLegende;
}

int Jeu::calculeNbColonnesAffichage(int _nbColonnesInit)
{
	// +1 pour la légende
	// +1 pour la séparation
	// +1 pour le trait de séparation
	return _nbColonnesInit + nbColonnesLegende;
}


void Jeu::setLegendeColonnes(vector< vector<string> > &_affichage)
{
	int nbColonnes = _affichage[0].size();
	
	for (int icol = 0; icol < nbColonnesLegende; icol++)
	{
		if(icol == 1)
		{
			_affichage[0][icol] = espaceVide;
		}
		else
		{
			_affichage[0][icol] = " ";
		}
	}

	for(int icol = nbColonnesLegende; icol < nbColonnes ; icol++)
    {
		_affichage[0][icol] = " "+to_string(icol - 2)+ "  ";
	}
}

void Jeu::setLigneVide(vector< vector<string> > &_affichage, int _iLigne)
{
	int nbColonnes = _affichage[0].size();
	
	for(int icol = 0; icol < nbColonnes ; icol++)
    {
		_affichage[_iLigne][icol] = espaceVide;
	}
}

void Jeu::setLignePleine(vector< vector<string> > &_affichage, int _iLigne)
{
	int nbColonnes = _affichage[0].size();
	
	for (int icol = 0; icol < nbColonnesLegende; icol++)
	{
		if(icol == 1)
		{
			_affichage[_iLigne][icol] = espaceVide;
		}
		else
		{
			_affichage[_iLigne][icol] = " ";
		}
	}

	for(int icol = nbColonnesLegende; icol < nbColonnes ; icol++)
    {
		_affichage[_iLigne][icol] = "____";
	}
}

Jeu::~Jeu(void)
{
}
