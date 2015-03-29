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
	// TODO : positionner tous les pions des 2 joueurs normalment


	// TEMPO : pour les tests 
	vector<long> pionsIds = joueurs[iTour]->getPionsIds();
	// joueurs[iTour]->setPionDame(pionsIds[0]);
	driverGrille->poserPion(pionsIds[0], 3, 2);
	/*
	driverGrille->poserPion(pionsIds[0], 4, 3);
	driverGrille->poserPion(pionsIds[1], 3, 2);
	driverGrille->poserPion(pionsIds[2], 3, 4);
	driverGrille->poserPion(pionsIds[3], 5, 2);
	driverGrille->poserPion(pionsIds[4], 5, 4);
	*/

	vector<long> pionsIdsAversaire = joueurs[iTour + 1 %2]->getPionsIds();
	/*
	driverGrille->poserPion(pionsIdsAversaire[0], 3, 2);
	driverGrille->poserPion(pionsIdsAversaire[1], 3, 4);
	driverGrille->poserPion(pionsIdsAversaire[2], 5, 2);
	driverGrille->poserPion(pionsIdsAversaire[3], 5, 4);
	*/
}

void Dames::jouer()
{
	afficherTitre();
	afficherJoueurs();
	afficherJeu();

	ChoixPion * pionADeplacer = askQuelPionDeplacer();
	cout << "Pion a deplacer :" + pionADeplacer->getRepresentation() << endl;

	ChoixDeplacement * caseFinale = askOuDeplacerPion(pionADeplacer);
	cout << " Vers la case " << caseFinale->getRepresentation() << endl;
}

ChoixPion * Dames::askQuelPionDeplacer()
{
	map<long, bool> pionsJoueur = joueurs[iTour]->getPionsIdsEtIsDame();
	vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurs[iTour]->getSensVertical(), pionsJoueur);
	int choixJoueur;

	do
	{
		for (int iChoixPion = 0; iChoixPion < choixPions.size(); iChoixPion++)
		{
			cout << to_string(iChoixPion + 1) + " - " + choixPions.at(iChoixPion)->getRepresentation() << endl;
		}

		cout << joueurs[iTour % joueurs.size()]->getNom()
			<< ", ou souhaitez-vous poser un pion ? " ;
		cin >> choixJoueur;

	}while(choixJoueur < 1 || choixJoueur > choixPions.size());

	return choixPions[choixJoueur -1];
}

ChoixDeplacement * Dames::askOuDeplacerPion(ChoixPion * _pionADeplacer)
{
	map<long, bool> pionsJoueur = joueurs[iTour]->getPionsIdsEtIsDame();
	vector<ChoixDeplacement *> choixCases = driverGrille->getChoixCase(_pionADeplacer, joueurs[iTour]->getSensVertical(), pionsJoueur);

	int choixJoueur;

	do
	{
		for (int iChoixCase = 0; iChoixCase < choixCases.size(); iChoixCase++)
		{
			cout << to_string(iChoixCase + 1) + " - " + choixCases.at(iChoixCase)->getRepresentation() << endl;
		}

		cout << joueurs[iTour % joueurs.size()]->getNom()
			<< ", ou souhaitez-vous poser le pion ? " ;
		cin >> choixJoueur;

	}while(choixJoueur < 1 || choixJoueur > choixCases.size());

	return choixCases[choixJoueur -1];
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
