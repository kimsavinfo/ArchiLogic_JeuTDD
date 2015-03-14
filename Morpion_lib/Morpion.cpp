#include "stdafx.h"
#include "Morpion.h"


Morpion::Morpion() 
{
	nbColonnes = 3;
	nbLignes = 3;
	nbJoueurs = 2;
	nbPionsParJoueur = 5;
	controleur = new ControleurGrilleMorpion(nbColonnes, nbLignes);

	creerJoueurs();
}

void Morpion::jouer()
{
	// TEMPO
	/*
	for(int iTempo = 0; iTempo < 3; iTempo++)
	{
		poserPion();

		// system("cls");
		afficherJeu();

		// iTour++;
	}
	*/
	Joueur * joueurDeTest = joueurs[iTour % joueurs.size()];
	vector<ChoixDeplacement*> choix = controleur->getChoix();
	long idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
	long idCaseChoisie = choix[2]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	joueurDeTest->poserPion(idPionChoisi);

	Joueur * joueurDeTest2 =  joueurs[iTour +1 % joueurs.size()];

	idCaseChoisie = choix[0]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest2->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[1]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[2]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest2->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[3]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[4]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest2->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[5]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[6]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest2->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[7]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
	idCaseChoisie = choix[8]->getIdCase();
	controleur->poserPion(idPionChoisi, idCaseChoisie);
	idPionChoisi = joueurDeTest2->getNextPionNonSurGrille()->getId();

	controleur->checkPartieFinie(idCaseChoisie, joueurDeTest2->getPions());

	afficherJeu();

	if(controleur->isPartieFinie())
		cout << "Partie finie" << endl;
	else
		cout << "Partie continue" << endl;

	cout << endl;

		
}


void Morpion::poserPion()
{
	long idPionChoisi = askJoueurQuelPionPoser();
	long idCaseChoisie = askJoueurOuPoserPion();

	controleur->poserPion(idPionChoisi, idCaseChoisie);
	joueurs[iTour % joueurs.size()]->poserPion(idPionChoisi);

	controleur->checkPartieFinie(idCaseChoisie, joueurs[iTour % joueurs.size()]->getPions());
}

long Morpion::askJoueurQuelPionPoser()
{
	// Pour le morpion, on n'a pas besoin de lui demande
	// On prend le un pion qui n'est pas encore posé
	return joueurs[iTour % joueurs.size()]->getNextPionNonSurGrille()->getId();
}

long Morpion::askJoueurOuPoserPion()
{
	vector<ChoixDeplacement*> choixDeplacement = controleur->getChoix();
	int choixMax = choixDeplacement.size();
	int choixJoueur;

	do
	{
		cout << "Choix possibles : " << endl;
		for (int iChoix = 0; iChoix < choixMax; iChoix++)
		{
			cout << choixDeplacement[iChoix]->getLegende() << endl;
		}

		cout << "Ou souhaitez-vous poser un pion, "
			<< joueurs[iTour % joueurs.size()]->getNom() + " ? " << endl;
		cin >> choixJoueur;
	}while(choixJoueur < 1 || choixJoueur > choixMax);

	return choixDeplacement[choixJoueur -1]->getIdCase();
}

/** ============================================================================================== */
/**	Affichage */
/** ============================================================================================== */

#pragma region Affichage

void Morpion::afficherTitre()
{
	cout << "========================" << endl;
	cout << "\tTic Tac Toe" << endl;
	cout << "========================" << endl;
}

void Morpion::afficherJeu()
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

map<int, map<int, string>> Morpion::construireRepresentation()
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
		jeuRepresentation[iLigneActu][1] = " ";
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

void  Morpion::insererLigneLegendeColonnes(map<int, map<int, string>> &_jeuRepresentation, int _largeurLigne)
{
	for(int iCol = 0; iCol < _largeurLigne; iCol++)
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

void Morpion::insererLigneVide(map<int, map<int, string>> & _jeuRepresentation, int _largeurLigne)
{
	int iLigneAInserer = _jeuRepresentation.size();
	
	for(int icol = 0; icol < _largeurLigne ; icol++)
    {
		_jeuRepresentation[iLigneAInserer][icol] = " ";
	}
}

void Morpion::insererLignePleine(map<int, map<int, string>> & _jeuRepresentation, int _largeurLigne)
{
	int iLigneAInserer = _jeuRepresentation.size();
	
	for(int icol = 0; icol < _largeurLigne ; icol++)
    {
		_jeuRepresentation[iLigneAInserer][icol] = "_";
	}
}

#pragma endregion Affichage

/** ============================================================================================== */
/**	GET */
/** ============================================================================================== */

#pragma region GET
map<long, Pion*> Morpion::getJoueursPions()
{
	map<long, Pion*> pions;

	for(int iJoueur = 0; iJoueur < nbJoueurs; iJoueur++)
	{
		map<long, Pion*> pionsJoueur = joueurs[iJoueur]->getPions();
		pions.insert(pionsJoueur.begin(), pionsJoueur.end());
	}

	return pions;
}

void Morpion::creerJoueurs()
{
	string noms[2] = {"Bob", "Alice"};
	string couleurs[2] = {"000000", "FFFFFF"};
	string formePion[2] = {"X", "O"};

	for(int iJoueur = 0; iJoueur < nbJoueurs; iJoueur++)
	{
		joueurs.push_back(new Joueur(noms[iJoueur], couleurs[iJoueur]));
		joueurs[iJoueur]->attribuerPions(nbPionsParJoueur, formePion[iJoueur]);
	}
}

#pragma endregion GET

Morpion::~Morpion(void)
{
	delete controleur;
}
