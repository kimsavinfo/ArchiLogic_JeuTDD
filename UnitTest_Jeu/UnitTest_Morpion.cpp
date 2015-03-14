#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
using namespace std;

#include "ControleurGrilleMorpion.h"
#include "Joueur.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Jeu
{
	static Joueur * joueurDeTest;
	static int nPionsParJoueur = 5;
	static int nbColonnes = 3;
	static int nbLignes = 3;
	
	TEST_CLASS(UnitTest_Morpion)
	{
	public:

		TEST_CLASS_INITIALIZE(ClassInitialize) 
		{
			joueurDeTest = new Joueur("Joueur Test", "000000");
			joueurDeTest->attribuerPions(nPionsParJoueur, "X");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			delete joueurDeTest;
		}

		/* Inidices d'une grille 3x3 :
			0	1	2
			3	4	5
			6	7	8
		*/

		TEST_METHOD(Test_LigneGagnante)
		{
			ControleurGrilleMorpion * controleur  = new ControleurGrilleMorpion(nbColonnes, nbLignes);
			vector<ChoixDeplacement*> choix = controleur->getChoix();
			long idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			long idCaseChoisie = choix[3]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			joueurDeTest->poserPion(idPionChoisi);

			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[4]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			joueurDeTest->poserPion(idPionChoisi);

			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[5]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			joueurDeTest->poserPion(idPionChoisi);

			controleur->checkPartieFinie(idCaseChoisie, joueurDeTest->getPions());

			Assert::IsTrue(controleur->isPartieFinie());
			Assert::IsFalse(controleur->isEgalite());
		}

		TEST_METHOD(Test_ColonneGagnante)
		{
			ControleurGrilleMorpion * controleur  = new ControleurGrilleMorpion(nbColonnes, nbLignes);
			vector<ChoixDeplacement*> choix = controleur->getChoix();
			long idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			long idCaseChoisie;
				
			idCaseChoisie = choix[1]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[4]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[7]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);

			controleur->checkPartieFinie(idCaseChoisie, joueurDeTest->getPions());

			Assert::IsTrue(controleur->isPartieFinie());
			Assert::IsFalse(controleur->isEgalite());
		}
		

		/*
		TEST_METHOD(Test_DiagoGagnanteGaucheDroite)
		{
			controleur->placerJeton(choix.at(0), joueurDeTest->getSymbole());
			controleur->placerJeton(choix.at(4), joueurDeTest->getSymbole());
			controleur->placerJeton(choix.at(8), joueurDeTest->getSymbole());

			Assert::IsTrue(controleur->isUnVainqueur());
		}

		TEST_METHOD(Test_DiagoGagnanteDroiteGauche)
		{
			controleur->placerJeton(choix.at(2), joueurDeTest->getSymbole());
			controleur->placerJeton(choix.at(4), joueurDeTest->getSymbole());
			controleur->placerJeton(choix.at(6), joueurDeTest->getSymbole());

			Assert::IsTrue(controleur->isUnVainqueur());
		}

		TEST_METHOD(Test_PartieGagneeAuDernierTour)
		{
			controleur->placerJeton(choix.at(0), 'X');
			controleur->placerJeton(choix.at(1), 'O');
			controleur->placerJeton(choix.at(2), 'O');
			controleur->placerJeton(choix.at(3), 'O');
			controleur->placerJeton(choix.at(4), 'X');
			controleur->placerJeton(choix.at(5), 'O');
			controleur->placerJeton(choix.at(6), 'O');
			controleur->placerJeton(choix.at(7), 'O');
			controleur->placerJeton(choix.at(8), 'X');

			Assert::IsTrue(controleur->isUnVainqueur());
		}

		TEST_METHOD(Test_PartieEgalite)
		{
			controleur->placerJeton(choix.at(0), 'X');
			controleur->placerJeton(choix.at(1), 'O');
			controleur->placerJeton(choix.at(2), 'O');
			controleur->placerJeton(choix.at(3), 'O');
			controleur->placerJeton(choix.at(4), 'X');
			controleur->placerJeton(choix.at(5), 'X');
			controleur->placerJeton(choix.at(6), '0');
			controleur->placerJeton(choix.at(7), 'X');
			controleur->placerJeton(choix.at(8), 'O');

			Assert::IsFalse(controleur->isUnVainqueur());
		}
		*/
	};
}