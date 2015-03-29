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
		int getLigneTempo();
		void setLigneTempo(int _ligneTempo);
		int getColonneTempo();
		void setColonneTempo(int _colonneTempo);
		void setCoordonneesTempo(int _ligneTempo, int _colonneTempo);
		virtual string getRepresentation();
		bool isDame();

	private:
		long idPion;
		int ligneDepart;
		int colonneDepart;
		bool typeDame;
		int ligneTempo;
		int colonneTempo;
};

