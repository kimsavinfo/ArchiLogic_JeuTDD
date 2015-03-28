#pragma once

#include "IRepresentation.h"

class ChoixPion : public IRepresentation
{
	public:
		ChoixPion(long _idPion, int _ligneDepart, int _colonneDepart);
		~ChoixPion(void);

		long getIdPion();
		int getLigneDepart();
		int getColonneDepart();
		virtual string getRepresentation();

	private:
		long idPion;
		int ligneDepart;
		int colonneDepart;
};

