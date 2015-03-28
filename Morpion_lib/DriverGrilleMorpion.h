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
		void checkPartieFinie(long _idCase, vector<long> _pionsJoueur);

	private:
		void checkLigneGagnante(int _iLigne, vector<long> _pionsJoueur);
		void checkColonneGagnante(int _iColonne, vector<long> _pionsJoueur);
		void checkDiagonaleNOSEGagnante(vector<long> _pionsJoueur);
		void checkDiagonaleNESOGagnante(vector<long> _pionsJoueur);
		void checkEgalite();
		void setPartieFinieEgalite(bool _egalite);
};
