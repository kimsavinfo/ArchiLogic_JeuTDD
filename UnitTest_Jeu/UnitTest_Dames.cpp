#include "stdafx.h"
#include "CppUnitTest.h"

#include "DriverGrilleDames.h"
#include "JoueurDames.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Jeu
{
	static int nbColonnes = 6;
	static int nbLignes = 6;
	/* Ne peut pas à cause du statut Dame des pions
	JoueurDames * joueurA;
	JoueurDames * joueurB;
	*/

	TEST_CLASS(UnitTest_Dames)
	{
		public:
		
			/*
			TEST_CLASS_INITIALIZE(ClassInitialize) 
			{
				joueurA = new JoueurDames("Alice", "W", 1);
				joueurB = new JoueurDames("Bob", "B", -1);
			}

			TEST_CLASS_CLEANUP(ClassCleanup)
			{
				delete joueurA;
				delete joueurB;
			}
			*/

			TEST_METHOD(Dames_PoserPion)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();

				driverGrille->poserPion(pionsIds[0], 0, 2);

				Assert::AreEqual(pionsIds[0], driverGrille->getCaseIdOccupant(0,2));
			}

			TEST_METHOD(Dames_ProposerPions_SansPionAutour)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 1, 1);
				driverGrille->poserPion(pionsIds[1], 3, 3);
				
				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 2, (int)choixPions.size() );
			}

			TEST_METHOD(Dames_ProposerPions_PionsJoueurVoisinsBloquant1)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 1, 1);
				driverGrille->poserPion(pionsIds[1], 2, 0);
				driverGrille->poserPion(pionsIds[2], 2, 2);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 2, (int)choixPions.size() );
			}

			TEST_METHOD(Dames_ProposerPions_PionsAdversairePeutEtreMange)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 3, 3);
				
				JoueurDames * joueurB = new JoueurDames("Bob", "B", -1);
				vector<long> pionsIdsAversaire = joueurB->getPionsIds();
				driverGrille->poserPion(pionsIdsAversaire[0], 4, 2);
				driverGrille->poserPion(pionsIdsAversaire[1], 4, 4);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 1, (int)choixPions.size() );
			}

			TEST_METHOD(Dames_ProposerPions_BloqueParDimensionGrille)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 4, 3);
				
				JoueurDames * joueurB = new JoueurDames("Bob", "B", -1);
				vector<long> pionsIdsAversaire = joueurB->getPionsIds();
				driverGrille->poserPion(pionsIdsAversaire[0], 5, 2);
				driverGrille->poserPion(pionsIdsAversaire[1], 5, 4);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 0, (int)choixPions.size() );
			}

			TEST_METHOD(Dames_ProposerPions_DameOK_NonEntouree)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				joueurA->setPionDame(pionsIds[0]);
				driverGrille->poserPion(pionsIds[0], 4, 3);
				
				JoueurDames * joueurB = new JoueurDames("Bob", "B", -1);
				vector<long> pionsIdsAversaire = joueurB->getPionsIds();
				driverGrille->poserPion(pionsIdsAversaire[0], 5, 2);
				driverGrille->poserPion(pionsIdsAversaire[1], 5, 4);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 1, (int)choixPions.size() );
			}

			TEST_METHOD(Dames_ProposerPions_DameOK_Entouree)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				joueurA->setPionDame(pionsIds[0]);
				driverGrille->poserPion(pionsIds[0], 4, 3);
				
				JoueurDames * joueurB = new JoueurDames("Bob", "B", -1);
				vector<long> pionsIdsAversaire = joueurB->getPionsIds();
				driverGrille->poserPion(pionsIdsAversaire[0], 3, 2);
				driverGrille->poserPion(pionsIdsAversaire[1], 3, 4);
				driverGrille->poserPion(pionsIdsAversaire[2], 5, 2);
				driverGrille->poserPion(pionsIdsAversaire[3], 5, 4);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 1, (int)choixPions.size() );
			}

			TEST_METHOD(Dames_ProposerPions_DameKO_Entouree)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				joueurA->setPionDame(pionsIds[0]);
				driverGrille->poserPion(pionsIds[0], 4, 3);
				driverGrille->poserPion(pionsIds[1], 3, 2);
				driverGrille->poserPion(pionsIds[2], 3, 4);
				driverGrille->poserPion(pionsIds[3], 5, 2);
				driverGrille->poserPion(pionsIds[4], 5, 4);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 2, (int)choixPions.size() );
			}

			TEST_METHOD(Dames_ProposerCases_PionSimpleSeul)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 3, 3);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);
				vector<ChoixDeplacement *> choixCases = driverGrille->getChoixCase(choixPions.at(0), joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 2, (int)choixCases.size() );
			}

			TEST_METHOD(Dames_ProposerCases_PionSimpleBloque)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 3, 3);
				driverGrille->poserPion(pionsIds[1], 4, 2);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);
				vector<ChoixDeplacement *> choixCases = driverGrille->getChoixCase(choixPions.at(0), joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 1, (int)choixCases.size() );
			}

			TEST_METHOD(Dames_ProposerCases_PionSimpleMangeObligation)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 3, 3);

				JoueurDames * joueurB = new JoueurDames("Bob", "B", -1);
				vector<long> pionsIdsAversaire = joueurB->getPionsIds();
				driverGrille->poserPion(pionsIdsAversaire[0], 4, 2);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);
				vector<ChoixDeplacement *> choixCases = driverGrille->getChoixCase(choixPions.at(0), joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 1, (int)choixCases.size() );
				Assert::AreEqual( 5, choixCases.at(0)->getLigneArrivee() );
				Assert::AreEqual( 1, choixCases.at(0)->getColonneArrivee() );
			}

			TEST_METHOD(Dames_ProposerCases_PionSimpleMangeRecursif)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				JoueurDames * joueurA = new JoueurDames("Alice", "W", 1);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 3, 3);

				JoueurDames * joueurB = new JoueurDames("Bob", "B", -1);
				vector<long> pionsIdsAversaire = joueurB->getPionsIds();
				driverGrille->poserPion(pionsIdsAversaire[0], 3, 2);
				driverGrille->poserPion(pionsIdsAversaire[1], 3, 4);

				map<long, bool> pionsJoueur = joueurA->getPionsIdsEtIsDame();
				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsJoueur);
				vector<ChoixDeplacement *> choixCases = driverGrille->getChoixCase(choixPions.at(0), joueurA->getSensVertical(), pionsJoueur);

				Assert::AreEqual( 1, (int)choixCases.size() );
				Assert::AreEqual( 2, choixCases.at(0)->getLigneArrivee() );
				Assert::AreEqual( 5, choixCases.at(0)->getColonneArrivee() );
			}
	};
}