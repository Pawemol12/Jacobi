// Jacobi.cpp : Implementacja algorytmu jacobiego z 1 normą
//
/**
* @author Paweł Lodzik & Tomasz Cwik
*/

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

#define typ float //Użyty typ zmiennoprzecinkowy jako typ elememntów wektorów, macierzy
int n; //Rozmiar macierzy
typ epsilon; // Pprzybliżenie epsilon
int MLI; //Maksymalna liczba iteracji

typ Alfa[200][200]; //Macierz alfa 
typ Beta[200]; //Wektor Beta

typ A[200][200]; //Macierz A
typ B[200]; //Macierz B

typ Xk1[200]; //X aktualnej iteracji
typ Xk[200]; //X poprzedniej iteracji

int iter = 0; //Aktualny numer iteracji

//Funkcja do wczytywania danych wejsciowych
bool funkcjaA() {
	string nazwaPliku;

	//Pobieranie danych wejściowych
	cout << "Podaj rozmiar macierzy A i wektorów B i X: ";
	cin >> n;

	cout << "Podaj dokładność epsilon: ";
	cin >> epsilon;
	cout << "Podaj MLI(maksymalną liczbę iteracji): ";
	cin >> MLI;

	cout << "Podaj nazwę pliku wejściowego: ";
	cin >> nazwaPliku;

	ifstream plikWejsciowy(nazwaPliku.c_str());

	if (!plikWejsciowy.is_open())             //Sprawdzenie czy udało się otworzyć plik
		return false;                //funkcja zwraca wartosc false jeśli to niemożliwe

	//Wczytywanie macierzy A z pliku
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			plikWejsciowy >> A[i][j];
			//cout << A[i][j] << " ";
		}
		//cout << endl;
	}

	//Wczytywanie wektora B z pliku
	for (int i = 1; i <= n; i++) {
		plikWejsciowy >> B[i];
	}

	plikWejsciowy.close(); //Zamykanie pliku wejściowego
	return true;
}

//Funkcja do obliczania macierzy Alfa i wektora Beta
bool funkcjaB() {
	for (int i = 1; i<n + 1; i++)
	{
		if (A[i][i] != 0) //Kontrola dzielenia przez 0
		{
			Beta[i] = B[i] / A[i][i];              //obliczanie wartosci wektora Beta
			for (int j = 1; j<n + 1; j++)
			{
				if (i == j) { //Wartosci na głównej przekątnej macierzy
					Alfa[i][j] = 0;     	//wpisywanie 0 po przekątnej
				}
				else {
					Alfa[i][j] = -(A[i][j] / A[i][i]); //obliczanie wspolczynnikow nielazacych na przekatnej
				}
			}

		}
		else {
			return false;//funkcja zwraca falsz jezeli niemozliwe jest obliczenie macierzy Alfa i Beta
		}
	}
	return true; //Funkcja zwraca prawde jesli pomyslnie obliczono macierz alfa i wektor beta
}

typ obliczNormeI() { //Funkcja do obliczania I normy
	typ max = 0.0;
	for (int i = 1; i < n + 1; i++) {

		//cout << 'Xk1' << Xk1[i] << 'Xk' << Xk[i] << endl;

		typ x = abs(Xk1[i] - Xk[i]); // Wartosc bezwzgledna z aktualnego elementu aktualnego wektora X - poprzedniego elementu wektora X
		//cout << "Petla " << i << " X " << x  << endl;
		if (x > max) {
			max = x;
		}
	}
	return max;
}

//Funkcja realizująca kolejne iteracje 
void funkcjaC() {

	typ norma = 0.0;
	typ pom = 0.0;

	//Wyznaczanie przyblizenia zerowego	
	for (int i = 1; i < n + 1; i++) {
		//Przepisujemy wektor Beta jako aktualne przyblizenie
		Xk1[i] = Beta[i];
	}
	//Wyznaczanie kolejnych przybliżeń
	do {
		for (int i = 1; i<n + 1; i++) 		// przepisanie aktualnego wektora rozwiązań jako rozwiązanie poprzednie
			Xk[i] = Xk1[i];
		
		//Wyznaczanie aktualnego wektora
		for (int i = 1; i<n + 1; i++)
		{
			pom = 0.0;
			for (int j = 1; j < n + 1; j++) {
				if (i != j) {
					pom += (Alfa[i][j] * Xk[j]);
				}
			}

			Xk1[i] = pom + Beta[i];
		}

		iter++; //inkrementacja licznika iteracji

		//Wyznaczanie normy
		norma = obliczNormeI();
	} while (iter < MLI && norma > epsilon);
}

//Funkcja generująca raport w pliku tekstowym
bool funkcjaD() {
	string nazwaRaportu;

	cout << "Podaj nazwe pliku tekstowego zawierajacego raport: ";
	cin >> nazwaRaportu;
	ofstream plikRaportu(nazwaRaportu);

	if (!plikRaportu.is_open()) // jeśli nie udało się utworzyc pliku zwracamy falsz
		return false;

	plikRaportu << "Macierz A:" << endl;        //wpisanie macierzy A do pliku zawierającego raport

	for (int i = 1; i<n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++) {
			plikRaportu << " " << A[i][j];
		}
		plikRaportu << endl;
	}
	plikRaportu << endl;

	plikRaportu << "Wektor B:" << endl;        //wpisanie wektora B do pliku zawierającego raport

	for (int i = 1; i < n + 1; i++) {
		plikRaportu << " " << B[i];
	}

	plikRaportu << endl << endl;

	plikRaportu << "Epsilon(wartosc przyblizenia) = " << epsilon << endl;
	plikRaportu << "MLI(maksymalna liczba iteracji) = " << MLI << endl;

	plikRaportu << endl <<  "Macierz Alfa:" << endl;

	for (int i = 1; i<n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++) {
			plikRaportu << " " << Alfa[i][j];
		}
		plikRaportu << endl;
	}

	plikRaportu << endl << "Wektor Beta:" << endl;
	for (int i = 1; i < n + 1; i++) {
		plikRaportu << " " << Beta[i];
	}
	plikRaportu << endl << endl;
	plikRaportu << "Liczba wykonanych iteracji wynosi " << iter << endl;

	//Ustawianie precyzji na 10 liczb znaczących oraz zmiana formatu na mantyse i ceche
	plikRaportu.precision(20);
	plikRaportu.setf(ios::scientific, ios::floatfield);                  //zmiana trybu wyswietlania liczb

	plikRaportu << "Wektor ostatnio wykonanej iteracji:" << endl;
	for (int k = 1; k < n + 1; k++) {
		plikRaportu << "\t" << Xk1[k] << endl;
	}

	plikRaportu <<  endl << endl << "Wektor przedostatnio wykonanej iteracji:" << endl;
	for (int k = 1; k < n + 1; k++) {
		plikRaportu << "\t" << Xk[k] << endl;
	}

	return true;
}


int main()
{
	if (funkcjaA()) { //Przypadek pomyślnego wczytania danych
		if (funkcjaB()) //Pomyślnie obliczono macierz alfa i wektor beta
		{
			funkcjaC();
			if (!funkcjaD()) {
				cout << "Nie udało się zapisać pliku wyjściowego z raportem!";
			}
		}
		else {
			cout << "Podczas obliczania macierzy alfa i wektora beta wystąpiło dzielenie przez zero!";
		}
	}
	else {
		cout << "Nie udało się otworzyć pliku o podanej nazwie";
	}

	system("pause");
    return 0;
}

