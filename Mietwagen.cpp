#include "Mietwagen.h"
#include "Fahrt.h"
#include <string>
#include <vector>
#include <iostream>

Mietwagen::Mietwagen(string marke, string kennzeichen, int sitze)
{
	Marke = marke;
	Kennzeichen = kennzeichen;
	Sitze = sitze;
}


void Mietwagen::printFahrzeug()
{
	cout << Marke.c_str() << ": " << Kennzeichen.c_str() << "\n" << "Sitze: " << Sitze << "\n";
}

void Mietwagen::alleFahrtenAnzeigen()
{
	cout << "\n";
	for (Fahrt fahrt : Fahrtenbuch)
	{
		fahrt.anzeigen();
	}
}

void Mietwagen::anmieten(Fahrt fahrt)
{
	if (verfuegbarkeitPruefen(fahrt) != -1)
	{
		cout << "Fahrt kollidiert mit folgender Buchung:\n";
		Fahrtenbuch.at(verfuegbarkeitPruefen(fahrt)).anzeigen();
		return;
	}
	cout << "Buchung mit Buchungsnummer \"" << fahrt.getBNr() << "\" erfolgreich\n";
	Fahrtenbuch.push_back(fahrt);
}

string& Mietwagen::getKennzeichen()
{
	return Kennzeichen;
}

int Mietwagen::bnrPruefen(int bnr)
{
	bool valid = true;
	int i = 0;
	for (i; i < Fahrtenbuch.size() && valid; i++)
	{
		valid &= Fahrtenbuch.at(i).getBNr() != bnr;
	}
	return valid ? -1 : i - 1;
}

void Mietwagen::fahrtAnzeigen(int bnr)
{
	bool valid = false;
	for (Fahrt fahrt : Fahrtenbuch)
	{
		if (fahrt.getBNr() == bnr)
		{
			valid = true;
			fahrt.anzeigen();
		}
	}
	if (!valid)
	{
		cout << "Buchungsnummer nicht gefunden\n";
	}
}

bool Mietwagen::fahrtLoeschen(int bnr)
{
	bool valid = false;
	for (int i = 0; i < Fahrtenbuch.size() && !valid; i++)
	{
		if (Fahrtenbuch.at(i).getBNr() == bnr)
		{
			valid = true;
			Fahrtenbuch.erase(Fahrtenbuch.begin() + i);
		}
	}
	return valid;
}

int Mietwagen::verfuegbarkeitPruefen(Fahrt fahrt)
{
	int i = 0;
	bool valid = true;
	for (i; i < Fahrtenbuch.size() && valid; i++)
	{
		valid &= !((fahrt.getBeginn() <= Fahrtenbuch.at(i).getBeginn()) && (fahrt.getEnde() > Fahrtenbuch.at(i).getBeginn()));
		valid &= !((fahrt.getBeginn() < Fahrtenbuch.at(i).getEnde()) && (fahrt.getEnde() >= Fahrtenbuch.at(i).getEnde()));
		valid &= !((fahrt.getBeginn() <= Fahrtenbuch.at(i).getBeginn()) && (fahrt.getEnde() >= Fahrtenbuch.at(i).getEnde()));
		valid &= !((fahrt.getBeginn() >= Fahrtenbuch.at(i).getBeginn()) && (fahrt.getEnde() <= Fahrtenbuch.at(i).getEnde()));
		valid &= !(fahrt.getBeginn() > fahrt.getEnde());
	}
	return valid ? -1 : i - 1;
}