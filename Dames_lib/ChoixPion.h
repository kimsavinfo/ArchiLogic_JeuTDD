#pragma once

#include "IRepresentation.h"

class ChoixPion : public IRepresentation
{
	public:
		ChoixPion(long _idPion, int _ligneDepart, int _colonneDepart, bool _typeDame);
		~ChoixPion(void);

		long getIdPion();
		int getLigneDepart();
		int getColonneDepart();
		virtual string getRepresentation();
		bool isDame();

	private:
		long idPion;
		int ligneDepart;
		int colonneDepart;
		bool typeDame;
};

