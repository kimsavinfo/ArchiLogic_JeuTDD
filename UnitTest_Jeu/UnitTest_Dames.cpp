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
				joueurA = new JoueurDames("Alice", "W");
				joueurB = new JoueurDames("Bob", "B");
			}

			TEST_CLASS_CLEANUP(ClassCleanup)
			{
				delete joueurA;
				delete joueurB;
			}

			TEST_METHOD(Dames_PoserPion)
			{
				DriverGrilleDames * driver  = new DriverGrilleDames(nbLignes, nbColonnes);
				vector<long> pionsIds = joueurA->getPionsIds();

				driver->poserPion(pionsIds[0], 0, 2);

				Assert::AreEqual(pionsIds[0], driver->getCaseIdOccupant(0,2));
			}
	};
}