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
		
		TEST_METHOD(Test_DiagoGagnanteNOSE)
		{
			ControleurGrilleMorpion * controleur  = new ControleurGrilleMorpion(nbColonnes, nbLignes);
			vector<ChoixDeplacement*> choix = controleur->getChoix();
			long idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			long idCaseChoisie;
				
			idCaseChoisie = choix[0]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[4]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[8]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);

			controleur->checkPartieFinie(idCaseChoisie, joueurDeTest->getPions());

			Assert::IsTrue(controleur->isPartieFinie());
			Assert::IsFalse(controleur->isEgalite());
		}
		
		TEST_METHOD(Test_DiagoGagnanteNESO)
		{
			ControleurGrilleMorpion * controleur  = new ControleurGrilleMorpion(nbColonnes, nbLignes);
			vector<ChoixDeplacement*> choix = controleur->getChoix();
			long idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			long idCaseChoisie;
				
			idCaseChoisie = choix[2]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[4]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);
			idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			idCaseChoisie = choix[6]->getIdCase();
			controleur->poserPion(idPionChoisi, idCaseChoisie);

			controleur->checkPartieFinie(idCaseChoisie, joueurDeTest->getPions());

			Assert::IsTrue(controleur->isPartieFinie());
			Assert::IsFalse(controleur->isEgalite());
		}

		
		TEST_METHOD(Test_PartieEgalite)
		{
			ControleurGrilleMorpion * controleur  = new ControleurGrilleMorpion(nbColonnes, nbLignes);
			vector<ChoixDeplacement*> choix = controleur->getChoix();
			long idPionChoisi = joueurDeTest->getNextPionNonSurGrille()->getId();
			long idCaseChoisie;
			
			Joueur * joueurDeTest2 = new Joueur("Joueur Test", "000000");
			joueurDeTest2->attribuerPions(nPionsParJoueur, "O");

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

			Assert::IsTrue(controleur->isPartieFinie());
			Assert::IsTrue(controleur->isEgalite());
		}
	};
}