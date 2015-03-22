#pragma once

#include <string> 
using namespace std;

class ChoixCase
{
	public:
		ChoixCase(string _legende, long _idCase);
		~ChoixCase(void);

		string getLegende();
		long getIdCase();

	private:
		string legende;
		long idCase;
};

