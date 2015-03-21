#include "stdafx.h"
#include "CppUnitTest.h"

#include "PionMorpion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Jeu
{
	

	TEST_CLASS(UnitTest_Morpion)
	{
	public:

		TEST_METHOD(Morpion_PionNonSurGrille)
		{
			PionMorpion * pion = new PionMorpion("X");
			Assert::IsFalse(pion->isSurGrille());
		}
		
	};
}