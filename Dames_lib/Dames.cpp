#include "stdafx.h"
#include "Dames.h"


Dames::Dames(void) : Jeu()
{
	driverGrille = new DriverGrilleDames(10, 10);

	initJeu();
}

/** ============================================================================================== */
/**	Initialiser le jeu : positionner les pions
/** ============================================================================================== */

void Dames::initJeu()
{
	ajouterJoueur("Alice", "W", 1);
	ajouterJoueur("Bob", "B", -1);

	driverGrille->initGrillePositionnerPions(
		joueurs.at(0)->getPionsIds(), joueurs.at(0)->getSensVertical()
	);
	driverGrille->initGrillePositionnerPions(
		joueurs.at(1)->getPionsIds(), joueurs.at(1)->getSensVertical()
	);
}

/* pour les tests 
void Dames::initJeu()
{
	driverGrille = new DriverGrilleDames(7, 7);

	vector<long> pionsIds = joueurs[iTour]->getPionsIds();
	joueurs[iTour]->setPionDame(pionsIds[0]);
	driverGrille->poserPion(pionsIds[0], 6, 2);

	vector<long> pionsIdsAversaire = joueurs[iTour + 1 %2]->getPionsIds();
	driverGrille->poserPion(pionsIdsAversaire[0], 4, 4);
	driverGrille->poserPion(pionsIdsAversaire[1], 2, 4);
	driverGrille->poserPion(pionsIdsAversaire[2], 3, 1);
}
*/

/** ============================================================================================== */
/**	Gestion d'un tour
/** ============================================================================================== */

void Dames::jouer()
{
	afficherTitre();
	afficherJoueurs();
	afficherJeu();

	do
	{
		ChoixPion * pionADeplacer = askQuelPionDeplacer();
		if(!driverGrille->isPartieFinie())
		{
			cout << "Deplacer le pion " + pionADeplacer->getRepresentation() << endl;
	
			ChoixDeplacement * caseFinale = askOuDeplacerPion(pionADeplacer);
			cout << "Vers la case " << caseFinale->getRepresentation() << endl;

			driverGrille->deplacerPion(pionADeplacer, caseFinale);
			mangerPions(caseFinale->getPionsManges());
			gererTypeDame(pionADeplacer->getIdPion());

			system("cls");

			afficherJeu();
			iTour++;
		}
		
	}while(!driverGrille->isPartieFinie());

	cout << joueurs[ (iTour-1) % joueurs.size()]->getNom() 
			<< " a gagne " << endl;
}

ChoixPion * Dames::askQuelPionDeplacer()
{
	map<long, bool> pionsJoueur = joueurs[iTour]->getPionsIdsEtIsDame();
	vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurs[iTour]->getSensVertical(), pionsJoueur);
	ChoixPion * pionADeplacer = NULL;
	
	if(choixPions.size() > 0)
	{
		int choixJoueur;

		do
		{
			for (int iChoixPion = 0; iChoixPion < choixPions.size(); iChoixPion++)
			{
				cout << to_string(iChoixPion + 1) + " - " + choixPions.at(iChoixPion)->getRepresentation() << endl;
			}

			cout << joueurs[iTour % joueurs.size()]->getNom()
				<< ", quel pion souhaitez-vous deplacer ? " ;
			cin >> choixJoueur;

			pionADeplacer = choixPions[choixJoueur -1];
		}while(choixJoueur < 1 || choixJoueur > choixPions.size());
	}
	else
	{
		driverGrille->setPartieFinie(true, false);
	}

	return pionADeplacer;
}

ChoixDeplacement * Dames::askOuDeplacerPion(ChoixPion * _pionADeplacer)
{
	map<long, bool> pionsJoueur = joueurs[iTour]->getPionsIdsEtIsDame();
	vector<ChoixDeplacement *> choixCases;
	
	if(joueurs[iTour]->isPionUneDame(_pionADeplacer->getIdPion()))
	{
		choixCases = driverGrille->getChoixCaseDame(_pionADeplacer, pionsJoueur); 
	}
	else
	{
		choixCases = driverGrille->getChoixCase(_pionADeplacer, joueurs[iTour]->getSensVertical(), pionsJoueur);
	}

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

void Dames::mangerPions(vector<long> _pionsManges)
{
	for (int iPionMange = 0; iPionMange < _pionsManges.size(); iPionMange++)
	{
		driverGrille->mangerPion(_pionsManges.at(iPionMange));
		joueurs[iTour + 1 %2]->mangerPion(_pionsManges.at(iPionMange));
	}
}


void Dames::gererTypeDame(long _idPionDeplace)
{
	if(!joueurs[iTour]->isPionUneDame(_idPionDeplace))
	{
		if( driverGrille->isPionDevientDame(_idPionDeplace, joueurs[iTour]->getSensVertical()) )
		{
			joueurs[iTour]->setPionDame(_idPionDeplace);
		}
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

/** ============================================================================================== */
/**	Destructeur
/** ============================================================================================== */


Dames::~Dames(void)
{
}
