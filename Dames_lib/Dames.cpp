#include "stdafx.h"
#include "Dames.h"


Dames::Dames(void) : Jeu()
{
	driverGrille = new DriverGrilleDames(6, 6);

	ajouterJoueur("Alice", "W", 1);
	ajouterJoueur("Bob", "B", -1);

	initJeu();
}

void Dames::initJeu()
{
	// TODO : positionner tous les pions des 2 joueurs
	// TEMPO : pour les tests 
	vector<long> pionsIds = joueurs[iTour]->getPionsIds();
	driverGrille->poserPion(pionsIds[0], 0, 0);
	// driverGrille->poserPion(pionsIds[1], 1, 1);
	// driverGrille->poserPion(pionsIds[1], 2, 2);
}

void Dames::jouer()
{
	afficherTitre();
	afficherJoueurs();
	afficherJeu();

	// TEMPO : pour les tests
	vector<long> pionsIds = joueurs[iTour]->getPionsIds();
	vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurs[iTour]->getSensVertical(), pionsIds);

	for (int iChoixPion = 0; iChoixPion < choixPions.size(); iChoixPion++)
	{
		cout << to_string(iChoixPion + 1) + " - " + choixPions.at(iChoixPion)->getRepresentation() << endl;
	}
}


/** ============================================================================================== */
/**	Affichage
/** ============================================================================================== */

void Dames::afficherJeu()
{
	vector< vector<string> > affichage = creerAffichage();

	cout << endl;
	for(int iLig = 0; iLig < affichage.size(); iLig++)
    {
		for(int iCol = 0; iCol < affichage[iLig].size(); iCol++)
        {
			cout << affichage[iLig][iCol];
		}
		cout << endl;
	}
	cout << endl;
}

vector< vector<string> > Dames::creerAffichage()
{ 
	int nbLignes = driverGrille->getGrilleNbLignes();
	int nbColonnes = driverGrille->getGrilleNbColonnes();
	vector< vector<string> > affichage = this->initAffichage(nbLignes, nbColonnes);
	string pionRepresentation;
	
	for(int iLigneGrille = 0; iLigneGrille < nbLignes; iLigneGrille++ )
	{
		for(int iColonneGrille = 0; iColonneGrille < nbColonnes; iColonneGrille++ )
		{
			affichage[iLigneGrille * 2 + nbLignesLegende][iColonneGrille + nbColonnesLegende] 
				= driverGrille->getCaseRepresentation(iLigneGrille, iColonneGrille);

			if(driverGrille->getCaseIdOccupant(iLigneGrille, iColonneGrille) > 0)
			{
				pionRepresentation = getPionRepresentation(driverGrille->getCaseIdOccupant(iLigneGrille, iColonneGrille));
				for(int iLettre = 0; iLettre < pionRepresentation.size(); iLettre++)
				{
					affichage[iLigneGrille * 2 + nbLignesLegende][iColonneGrille + nbColonnesLegende].at(1 + iLettre)
						= pionRepresentation[iLettre];
				}
			}
		}
	}

	return affichage;
}

string Dames::getPionRepresentation(long _idPion)
{
	string representation = "";

	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		if(joueurs[iJoueur]->isPionAuJoueur(_idPion))
		{
			representation = joueurs[iJoueur]->getPionRepresentation(_idPion);
		}
	}

	return representation;
}

void Dames::ajouterJoueur(string _nom, string _couleur, int _sensVertical)
{
	joueurs.push_back( new JoueurDames(_nom, _couleur, _sensVertical) );
}

void Dames::afficherJoueurs()
{
	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		cout << joueurs[iJoueur]->getNom() << " joue avec les pions " << joueurs[iJoueur]->getCouleurPions() << endl ;
	}
}

void Dames::afficherTitre()
{
	cout << "========================" << endl;
	cout << "\tDames" << endl;
	cout << "========================" << endl;
}

Dames::~Dames(void)
{
}
