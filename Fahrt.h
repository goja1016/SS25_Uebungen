#pragma once
#include <iostream>
#include <string>

using namespace std;

class Fahrt
{
private:
	int Beginn = 0;
	int Ende = 0;
	int BNr = 0;
	string Kunde;

public:
	Fahrt(int beginn, int ende, int bnr, string kunde);

	void anzeigen();
	int getBNr();
	int getBeginn();
	int getEnde();
};

