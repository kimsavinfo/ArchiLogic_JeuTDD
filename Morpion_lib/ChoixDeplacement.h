#include <string> 
using namespace std;

class ChoixDeplacement
{
	public:
		ChoixDeplacement(string _legende, long _idCase);
		~ChoixDeplacement(void);

		string getLegende();
		long getIdCase();

	private:
		string legende;
		long idCase;
};

