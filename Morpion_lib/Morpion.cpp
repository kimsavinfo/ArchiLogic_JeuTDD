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

	do
	{
		poserPion();

		system("cls");
		afficherJeu();

		iTour++;
	}while(!driverGrille->isPartieFinie());

	if(driverGrille->isEgalite())
	{
		cout << " ====> EGALITE " << endl;
	}
	else
	{
		cout << joueurs[ (iTour -1) % joueurs.size()]->getNom() 
			<< " a gagne " << endl;
	}
}

void Morpion::poserPion()
{
	long idPionChoisi = askJoueurQuelPionPoser();
	long idCaseChoisie = askJoueurOuPoserPion();

	driverGrille->poserPion(idPionChoisi, idCaseChoisie);
	joueurs[iTour % joueurs.size()]->poserPion(idPionChoisi);

	driverGrille->checkPartieFinie(idCaseChoisie, joueurs[iTour % joueurs.size()]->getPionsIds());
}

long Morpion::askJoueurQuelPionPoser()
{
	// Pour le morpion, on n'a pas besoin de lui demande
	// On prend le un pion qui n'est pas encore posé
	return joueurs[iTour % joueurs.size()]->getIdPionAPoser();
}

long Morpion::askJoueurOuPoserPion()
{
	vector<ChoixCase *> choix = driverGrille->getChoixCases();
	int choixMax = choix.size();
	int choixJoueur;

	do
	{
		cout << "Choix possibles [ligne ; colonne] : " << endl;
		for (int iChoix = 0; iChoix < choixMax; iChoix++)
		{
			cout << choix[iChoix]->getLegende() << endl;
		}

		cout << joueurs[iTour % joueurs.size()]->getNom()
			<< ", ou souhaitez-vous poser un pion ? " 
			<< endl;
		cin >> choixJoueur;
	}while(choixJoueur < 1 || choixJoueur > choixMax);

	return choix[choixJoueur -1]->getIdCase();
}

/** ============================================================================================== */
/**	Joueur
/** ============================================================================================== */

void Morpion::ajouterJoueur(string _nom, string _formePions)
{
	joueurs.push_back( new JoueurMorpion(_nom, _formePions) );
}

void Morpion::afficherJoueurs()
{
	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		cout << joueurs[iJoueur]->getNom() << " joue avec les pions " << joueurs[iJoueur]->getFormePions() << endl ;
	}
}

/** ============================================================================================== */
/**	Affichage
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


vector< vector<string> > Morpion::creerAffichage()
{ 
	int nbLignes = driverGrille->getGrilleNbLignes();
	int nbColonnes = driverGrille->getGrilleNbColonnes();
	vector< vector<string> > affichage = this->initAffichage(nbLignes, nbColonnes);
	
	for(int iLigneGrille = 0; iLigneGrille < nbLignes; iLigneGrille++ )
	{
		for(int iColonneGrille = 0; iColonneGrille < nbColonnes; iColonneGrille++ )
		{
			affichage[iLigneGrille * 2 + nbLignesLegende][iColonneGrille + nbColonnesLegende] 
				= driverGrille->getCaseRepresentation(iLigneGrille, iColonneGrille);

			if(driverGrille->getCaseIdOccupant(iLigneGrille, iColonneGrille) > 0)
			{
				for(int iJoueur = 0; iJoueur < joueurs.size() ; iJoueur++)
				{
					if( joueurs.at(iJoueur)->isPionAuJoueur(driverGrille->getCaseIdOccupant(iLigneGrille, iColonneGrille)) )
					{
						affichage[iLigneGrille * 2 + nbLignesLegende][iColonneGrille + nbColonnesLegende].at(1) 
						= joueurs.at(iJoueur)->getFormePions()[0];
					}	
				}
			}
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
