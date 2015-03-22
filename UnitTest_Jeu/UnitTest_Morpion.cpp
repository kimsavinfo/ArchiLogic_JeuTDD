#include "stdafx.h"
#include "CppUnitTest.h"

#include "JoueurMorpion.h"
#include "DriverGrilleMorpion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Jeu
{
	static JoueurMorpion * joueurDeTest;
	static int nbColonnes = 3;
	static int nbLignes = 3;

	TEST_CLASS(UnitTest_Morpion)
	{
		public:

			TEST_CLASS_INITIALIZE(ClassInitialize) 
			{

				joueurDeTest = new JoueurMorpion("Joueur Test", "X");
			}

			TEST_CLASS_CLEANUP(ClassCleanup)
			{
				delete joueurDeTest;
			}

			// =================== TESTS UNITAIRES ===================
			/* Inidices d'une grille 3x3 :
				0	1	2
				3	4	5
				6	7	8
			*/

			TEST_METHOD(Morpion_PionNonSurGrille)
			{
				PionMorpion * pion = new PionMorpion("X");
				Assert::IsFalse(pion->isSurGrille());
			}

			TEST_METHOD(Test_LigneGagnante)
			{
				DriverGrilleMorpion * driver  = new DriverGrilleMorpion(nbColonnes, nbLignes);
				vector<ChoixCase *> choix = driver->getChoixCases();

				poserPion(joueurDeTest, driver, choix, 3);
				poserPion(joueurDeTest, driver, choix, 4);
				poserPion(joueurDeTest, driver, choix, 5);

				Assert::IsTrue(driver->isPartieFinie());
				Assert::IsFalse(driver->isEgalite());
			}
		
		private:
			void poserPion(JoueurMorpion *_joueur, DriverGrilleMorpion * _driver, vector<ChoixCase *> &_choix, int _iChoix)
			{
				long idPionChoisi = _joueur->getPionAPoser()->getId();
				long idCaseChoisie = _choix[_iChoix]->getIdCase();
				_driver->poserPion(idPionChoisi, idCaseChoisie);
				_joueur->poserPion(idPionChoisi);
				_driver->checkPartieFinie(idCaseChoisie, joueurDeTest->getPions());
			};

	};
}