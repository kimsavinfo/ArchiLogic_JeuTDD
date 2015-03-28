#pragma once

#include <algorithm>

#include "DriverGrille.h"
#include "ChoixPion.h"

class DriverGrilleDames : public DriverGrille
{
	public:
		DriverGrilleDames(int _nbLignes, int _nbColonnes);
		~DriverGrilleDames(void);

		void poserPion(long _idPion, int _iLigne, int _iColonne);
		map<string, int> getCaseCoordonneesOccupant(long _idOccupant);
		vector<ChoixPion *> getChoixPions(int _sensVertical, vector<long> _pionsIdsJoueur);

	private:
		bool isPionDeplacable(int _ligne, int _colonne, int _sensVertical, int _sensHorizontal, vector<long> _pionsIdsJoueur);
		bool isCaseOccupeeParPionAdverse(int _ligne, int _colonne, vector<long> _pionsIdsJoueur);
};

