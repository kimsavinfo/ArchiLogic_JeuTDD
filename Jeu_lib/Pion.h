#include <string>
using namespace std;

#include "IRepresentation.h"

class Pion : public IRepresentation
{
	public:
		Pion(string _forme);
		~Pion(void);

		virtual string getRepresentation();

	protected:
		long idPion;
		string representation;
};

