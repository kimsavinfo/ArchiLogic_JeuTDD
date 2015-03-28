#pragma once

#include "Pion.h"

class PionDames : public Pion
{
	public:
		PionDames(string _couleur);
		~PionDames(void);

		string getCouleur();
		virtual string getRepresentation();
		bool isDame();
		void setDame();

	private:
		bool typeDame;
};

