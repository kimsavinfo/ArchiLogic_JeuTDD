#include "stdafx.h"
#include "Morpion.h"


Morpion::Morpion(void) : Jeu()
{
	driverGrille = new DriverGrilleMorpion(3, 3);
	iTour = 0;

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

		// iTour
	}while(!driverGrille->isPartieFinie());

	/*
	if(driverGrille->isPartieFinie())
	{
		cout << " ====> PARTIE FINIE " << endl;
	}
	else
	{
		cout << " EN COURS " << endl;
	}
	*/

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

	driverGrille->checkPartieFinie(idCaseChoisie, joueurs[iTour % joueurs.size()]->getPions());
}

long Morpion::askJoueurQuelPionPoser()
{
	// Pour le morpion, on n'a pas besoin de lui demande
	// On prend le un pion qui n'est pas encore posé
	return joueurs[iTour % joueurs.size()]->getPionAPoser()->getId();
}

long Morpion::askJoueurOuPoserPion()
{
	vector<ChoixCase *> choix = driverGrille->getChoixCases();
	int choixMax = choix.size();
	int choixJoueur;

	do
	{
		cout << "Choix possibles : " << endl;
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
	Grille * grille = driverGrille->getGrille();
	map<long, PionMorpion*> pions = getJoueursPions();
	int nbLignes = grille->getNbLignes();
	int nbColonnes = grille->getNbColonnes();
	vector< vector<string> > affichage = this->initAffichage(nbLignes, nbColonnes);
	Case * caseAAffciher;
	
	for(int iLigneGrille = 0; iLigneGrille < nbLignes; iLigneGrille++ )
	{
		for(int iColonneGrille = 0; iColonneGrille < nbColonnes; iColonneGrille++ )
		{
			caseAAffciher = grille->getCase(iLigneGrille, iColonneGrille);

			affichage[iLigneGrille * 2 + nbLignesLegende][iColonneGrille + nbColonnesLegende] 
				= caseAAffciher->getRepresentation();

			if(caseAAffciher->getIdOccupant() > 0)
			{
				affichage[iLigneGrille * 2 + nbLignesLegende][iColonneGrille + nbColonnesLegende].at(1) 
					= pions[caseAAffciher->getIdOccupant()]->getRepresentation()[0];
			}
		}
	}

	return affichage;
}

map<long, PionMorpion *> Morpion::getJoueursPions()
{
	map<long, PionMorpion*> pions;

	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		map<long, PionMorpion*> pionsJoueur = joueurs[iJoueur]->getPions();
		pions.insert(pionsJoueur.begin(), pionsJoueur.end());
	}

	return pions;
}


Morpion::~Morpion(void)
{
	delete driverGrille;

	for(int iJoueur = 0; iJoueur < joueurs.size(); iJoueur++)
	{
		delete joueurs.at(iJoueur);
	}
}
