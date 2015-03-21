#include "stdafx.h"
#include "CppUnitTest.h"

#include "JoueurMorpion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Jeu
{
	TEST_CLASS(UnitTest_Jeu)
	{
	public:
		
		TEST_METHOD(Jeu_InterfaceBienImplementee)
		{
			Pion * pion = new Pion("X");
			Assert::AreEqual(0, strcmp("X", pion->getRepresentation().c_str()));
		}

		TEST_METHOD(Jeu_FactoryBienImplementee)
		{
			JoueurMorpion * joueur = new JoueurMorpion("Alice", "X");
			map<long, PionMorpion*> pions = joueur->getPions();

			int nbTrue = 0;
			for (auto const& pion: pions)
			{
				if( strcmp("X", pion.second->getRepresentation().c_str()) == 0 && !pion.second->isSurGrille())
				{
					nbTrue++;
				}
			}

			Assert::AreEqual(5, nbTrue);
		}

	};
}