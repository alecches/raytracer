#include <iostream>
#include "Canvas.h"
#include "Color.h"
#include "Matrix.h"
using namespace std;


int main() {
	
	Matrix m(4, 4);
	m <<
		-5, 2, 6, -8,
		1, -5, 1, 8,
		7, 7, -6, -7,
		1, -3, 7, 4;

	Matrix inv = m.inverse();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4;j++) {
			cout << inv(i, j) <<  '  ';
		}
		cout << '\n';
	}

	return 0;
}
