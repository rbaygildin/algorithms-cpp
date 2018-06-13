//#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <assert.h>

#include "DNARepairer.h"

using namespace std;

void testAddGetElementAndListSize();
void testAddNodeToEndDeleteNodes();

int main (int argc, char* argv[])
{
	/*
	try{
		DNARepairer dnarepairer;

		dnarepairer.readFile("test.in");

		cout << "Broken DNAs" << endl;
		dnarepairer.printDNAStorage();

		dnarepairer.repairDNA();

		cout << "Good as it is" << endl;
		dnarepairer.printDNAStorage();
	}
	catch(exception &e) {
		cout << e.what();
	}
	catch (...){
		cout << "Something wrong happend." << endl;
	}
	 */
	DNARepairer dnaRepairer;
	cout << "BAD DNA" << endl;
	dnaRepairer.readFile("test2.in");
	dnaRepairer.printDNAStorage();
	dnaRepairer.repairDNA();
	cout << "GOOD DNA" << endl;
	dnaRepairer.printDNAStorage();
	return EXIT_SUCCESS;
}


