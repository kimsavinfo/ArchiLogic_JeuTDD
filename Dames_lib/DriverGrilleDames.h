#pragma once

#include "DriverGrille.h"
#include "ChoixPion.h"

class DriverGrilleDames : public DriverGrille
{
	public:
		DriverGrilleDames(int _nbLignes, int _nbColonnes);
		~DriverGrilleDames(void);

		void poserPion(long _idPion, int _iLigne, int _iColonne);
		map<string, int> getCaseCoordonneesOccupant(long _idOccupant);
		vector<ChoixPion *> getChoixPions(int _sensVertical, map<long, bool> _pionsJoueur);

	private:
		bool isPionDeplacable(int _ligne, int _colonne, int _sensVertical, int _sensHorizontal, map<long, bool> _pionsJoueur);
		bool isPionSimpleDeplacable(int _ligne, int _colonne, int _sensVertical, map<long, bool> _pionsJoueur);
		bool isPionDameDeplacable(int _ligne, int _colonne,map<long, bool> _pionsJoueur );
		bool isCaseOccupeeParPionAdverse(int _ligne, int _colonne, map<long, bool> _pionsJoueur);
};

