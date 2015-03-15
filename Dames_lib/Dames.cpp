#include "stdafx.h"
#include "Dames.h"


Dames::Dames()
{
	nbColonnes = 10;
	nbLignes = 10;
	nbJoueurs = 2;
	nbPionsParJoueur = 20;
	controleur = new ControleurGrilleDames(nbColonnes, nbLignes);

	creerJoueurs();
}

/** ============================================================================================== */
/**	Affichage */
/** ============================================================================================== */

#pragma region Affichage

void Dames::afficherTitre()
{
	cout << "========================" << endl;
	cout << "\tDames" << endl;
	cout << "========================" << endl;
}

void Dames::afficherJeu()
{
	map<int, map<int, string>> jeuRepresentation = construireRepresentation();

	for(int iLig = 0; iLig < jeuRepresentation.size(); iLig++)
    {
		for(int iCol = 0; iCol < jeuRepresentation[iLig].size(); iCol++)
        {
			cout << jeuRepresentation[iLig][iCol];
		}
		cout << endl;
	}
}

map<int, map<int, string>> Dames::construireRepresentation()
{

	map<int, map<int, string>> jeuRepresentation;
	int largeurTotale = 3 + controleur->getGrilleLargeur();
	string caseRepresentation;
	long idOccupant = 0;

	map<long, Pion*> pions = getJoueursPions();
	map<int, map<int,  map<long, Case*>>> cases = controleur->getGrilleCases();

	insererLigneLegendeColonnes(jeuRepresentation, largeurTotale);
	insererLigneVide(jeuRepresentation, largeurTotale);

	int iLigneActu = 2;
	int iColonneActu = 2;
	for(int iLig = 0; iLig < nbLignes; iLig++)
    {
		jeuRepresentation[iLigneActu][0] = to_string(iLig + 1);
		jeuRepresentation[iLigneActu][1] = "\t";
		jeuRepresentation[iLigneActu][2] = "|";

		iColonneActu = 3;
        for(int iCol = 0; iCol < nbColonnes; iCol++)
        {
            for (auto const& uneCase: cases[iLig][iCol])
			{
				caseRepresentation = uneCase.second->afficher();
				idOccupant = uneCase.second->getIdOccupant();

				if( idOccupant > 0 )
				{
					string pionRepresentation = pions.at(idOccupant)->afficher();
					caseRepresentation.replace(1, pionRepresentation.length(), pionRepresentation);
				}

				for(char& character : caseRepresentation) 
				{
					jeuRepresentation[iLigneActu][iColonneActu] = character;
					iColonneActu++;
				}
			}
        }
		iLigneActu++;

		insererLignePleine(jeuRepresentation, largeurTotale);
		iLigneActu++;
	}

	return jeuRepresentation;
}

void  Dames::insererLigneLegendeColonnes(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne)
{
	_jeuRepresentation[0][0] = " ";
	_jeuRepresentation[0][1] = "\t";
	_jeuRepresentation[0][2] = " ";

	for(int iCol = 3; iCol < _largeurLigne; iCol++)
    {
		int colonneLegende = iCol % 4;
		if(colonneLegende % 4 == 0 && iCol > 0)
		{
			_jeuRepresentation[0][iCol] = to_string(iCol / 4);
		}
		else
		{
			_jeuRepresentation[0][iCol] = " ";
		}
	}
}

void Dames::insererLigneVide(map<int, map<int, string>> & _jeuRepresentation, int _largeurLigne)
{
	int iLigneAInserer = _jeuRepresentation.size();
	
	for(int icol = 0; icol < _largeurLigne ; icol++)
    {
		_jeuRepresentation[iLigneAInserer][icol] = " ";
	}
}

void Dames::insererLignePleine(map<int, map<int, string>> & _jeuRepresentation, int _largeurLigne)
{
	int iLigneAInserer = _jeuRepresentation.size();
	
	_jeuRepresentation[iLigneAInserer][0] = " ";
	_jeuRepresentation[iLigneAInserer][1] = "\t";
	_jeuRepresentation[iLigneAInserer][2] = "|";

	for(int icol = 3; icol < _largeurLigne ; icol++)
    {
		_jeuRepresentation[iLigneAInserer][icol] = "_";
	}
}

#pragma endregion

/** ============================================================================================== */
/**	GET */
/** ============================================================================================== */

#pragma region GET
map<long, Pion*> Dames::getJoueursPions()
{
	map<long, Pion*> pions;

	for(int iJoueur = 0; iJoueur < nbJoueurs; iJoueur++)
	{
		map<long, Pion*> pionsJoueur = joueurs[iJoueur]->getPions();
		pions.insert(pionsJoueur.begin(), pionsJoueur.end());
	}

	return pions;
}
#pragma endregion GET

void Dames::creerJoueurs()
{
	string noms[2] = {"Bob", "Alice"};
	string couleurs[2] = {"000000", "FFFFFF"};
	string formePion[2] = {"O", "O"};

	for(int iJoueur = 0; iJoueur < nbJoueurs; iJoueur++)
	{
		joueurs.push_back(new Joueur(noms[iJoueur], couleurs[iJoueur]));
		joueurs[iJoueur]->attribuerPions(nbPionsParJoueur, formePion[iJoueur]);
	}
}

Dames::~Dames(void)
{
	delete controleur;
}
