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

		TEST_METHOD(Jeu_GrilleBienImplementee)
		{
			int nbLignes = 2;
			int nbColonnes = 2;
			Grille * grille = new Grille(nbLignes, nbColonnes);
			vector< vector<Case *> > cases =  grille->getCases();

			int nbTrue = 0;
			for(int iLig = 0; iLig < nbLignes; iLig++)
			{
				for(int iCol = 0; iCol < nbColonnes; iCol++)
				{
					if(cases[iLig][iCol]->getIdOccupant() == 0)
					{
						nbTrue++;
					}
				}
			}
			
			Assert::AreEqual(4, nbTrue);
		}

	};
}