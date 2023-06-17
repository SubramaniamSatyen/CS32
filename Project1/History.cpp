//class History
//{
//public:
//	History(int nRows, int nCols);
//	bool record(int r, int c);
//	void display() const;
//};
#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	m_r = nRows;
	m_c = nCols;
	for (int r = 0; r < m_r; r++)
		for (int c = 0; c < m_c; c++)
			m_hist[r][c] = '.';
}

bool History::record(int r, int c) {
	if (r > m_r || c > m_c || r <= 0 || c <= 0) {
		return false;
	}
	r--;
	c--;
	//Record current location
	if (m_hist[r][c] == '.') {
		m_hist[r][c] = 'A';
	}
	else if ( 'Z' - m_hist[r][c] > 0 && 'Z' - m_hist[r][c] <= 25) {
		m_hist[r][c]++;
	}
	else {
		m_hist[r][c] = 'Z';
	}
	return true;
}

void History::display() const {
	clearScreen();
	//Print out locations
	for (int r = 0; r < m_r; r++)
	{
		for (int c = 0; c < m_c; c++)
			cout << m_hist[r][c];
		cout << endl;
	}
	cout << endl;
}