// TMP_lab_No5_OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Source.h"
using namespace std;
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "incorrect command line! "
			"Waited: command in_file out_file"
			<< endl;
		exit(1);
	}
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);

	fileCheck(ifst);

	ifst.close();
	ifst.open(argv[1]);

	cout << "Start" << endl;
	container c;
	c.In(ifst);
	ofst << "Filled container. " << endl;
	c.Out(ofst);
	c.Sort();
	ofst << endl;
	c.Out(ofst);
	ofst << endl;
	c.OutFeature(ofst);
	c.Clear();
	ofst << "Empty container. " << endl;
	c.Out(ofst);
	cout << "Stop" << endl;
	return 0;
}