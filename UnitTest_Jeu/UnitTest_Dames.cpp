#include "stdafx.h"
#include "CppUnitTest.h"

#include "DriverGrilleDames.h"
#include "JoueurDames.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Jeu
{
	static int nbColonnes = 6;
	static int nbLignes = 6;
	static JoueurDames * joueurA;
	static JoueurDames * joueurB;

	TEST_CLASS(UnitTest_Dames)
	{
		public:
		
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

			TEST_METHOD(Dames_PoserPion)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				vector<long> pionsIds = joueurA->getPionsIds();

				driverGrille->poserPion(pionsIds[0], 0, 2);

				Assert::AreEqual(pionsIds[0], driverGrille->getCaseIdOccupant(0,2));
			}

			TEST_METHOD(Dames_ProposerPions_SansPionAutour)
			{
				DriverGrilleDames * driverGrille  = new DriverGrilleDames(nbLignes, nbColonnes);
				vector<long> pionsIds = joueurA->getPionsIds();
				driverGrille->poserPion(pionsIds[0], 1, 1);
				driverGrille->poserPion(pionsIds[0], 3, 3);

				vector<ChoixPion *> choixPions = driverGrille->getChoixPions(joueurA->getSensVertical(), pionsIds);

				Assert::AreEqual( 2, (int)choixPions.size() );
			}
	};
}