#include <iostream>
#include "tartagliaTriangle.h"

using namespace std;

int main()
{
	tartagliaTriangle tar;

	tar.setRowsToPrint(10);
	tar.printTriangle(cout);

	return 0;
}