#include "stdafx.h"
#include "CppUnitTest.h"

#include "DriverGrilleDames.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Jeu
{
	static int nbColonnes = 6;
	static int nbLignes = 6;

	TEST_CLASS(UnitTest_Dames)
	{
		public:
		
			TEST_METHOD(Dames_initGrille)
			{
				DriverGrilleDames * driver  = new DriverGrilleDames(nbLignes, nbColonnes);

				Assert::AreEqual(nbLignes , driver->getGrilleNbLignes());
				Assert::AreEqual(nbColonnes , driver->getGrilleNbColonnes());
			}

	};
}