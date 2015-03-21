#include "stdafx.h"
#include "Jeu.h"


Jeu::Jeu(void)
{
	espaceVide = "    ";
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

	for (int iLigne = 0; iLigne < _nbLignes; iLigne++)
	{
		affichage.push_back( vector<string>() );

		for (int iColonne = 0; iColonne < _nbColonnes; iColonne++)
		{
			affichage[iLigne].push_back(espaceVide);

			if(iLigne > 1)
			{
				if(iColonne == 0)
				{
					affichage[iLigne][iColonne] = to_string(iLigne / 2 -1);
				}
				else if(iColonne == 2)
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

void Jeu::setLegendeColonnes(vector< vector<string> > &_affichage)
{
	int nbColonnes = _affichage[0].size();
	
	for (int icol = 0; icol < 3; icol++)
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

	for(int icol = 3; icol < nbColonnes ; icol++)
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
	
	for (int icol = 0; icol < 3; icol++)
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

	for(int icol = 3; icol < nbColonnes ; icol++)
    {
		_affichage[_iLigne][icol] = "____";
	}
}

Jeu::~Jeu(void)
{
}
