#include "stdafx.h"
#include "CppUnitTest.h"

#include "JoueurMorpion.h"
#include "Grille.h"

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
			vector<long> pions = joueur->getPionsIds();

			int nbTrue = 0;
			for(int iPion = 0; iPion < pions.size(); iPion++)
			{
				if( pions.at(iPion) != 0 )
				{
					nbTrue++;
				}
			}

			Assert::AreEqual(5, nbTrue);
		}

		TEST_METHOD(Jeu_GrilleBienImplementee)
		{
			int nbLignes = 2;
			int nbColonnes = 2;
			Grille * grille = new Grille(nbLignes, nbColonnes);

			int nbTrue = 0;
			for(int iLig = 0; iLig < nbLignes; iLig++)
			{
				for(int iCol = 0; iCol < nbColonnes; iCol++)
				{
					if(grille->getCaseIdOccupant(iLig, iCol) == 0)
					{
						nbTrue++;
					}
				}
			}
			
			Assert::AreEqual(4, nbTrue);
		}

	};
}