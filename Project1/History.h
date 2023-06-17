#ifndef HISTORY
#define HISTORY

#include "globals.h"

class History
{
	public:
		History(int nRows, int nCols);
		bool record(int r, int c);
		void display() const;
	private:
		int m_r;
		int m_c;
		char m_hist[MAXROWS][MAXCOLS];
};

#endif //HISTORY