#pragma once

#include <map>

#include "DriverGrille.h"
#include "ChoixCase.h"
#include "PionMorpion.h"

class DriverGrilleMorpion : public DriverGrille
{
	public:
		DriverGrilleMorpion(int _nbLignes, int _nbColonnes);
		~DriverGrilleMorpion(void);

		vector<ChoixCase *> getChoixCases();
		void poserPion(long _idPion, long _idCase);
		void checkPartieFinie(long _idCase, map<long, PionMorpion*> _pionsJoueur);

	private:
		void checkLigneGagnante(int _iLigne, map<long, PionMorpion*> _pionsJoueur);
		void checkColonneGagnante(int _iColonne, map<long, PionMorpion*> _pionsJoueur);
		void checkDiagonaleNOSEGagnante(map<long, PionMorpion*> _pionsJoueur);
		void checkDiagonaleNESOGagnante(map<long, PionMorpion*> _pionsJoueur);
		void checkEgalite();
		void setPartieFinieEgalite(bool _egalite);
};
