// Jacobi.cpp : Implementacja algorytmu jacobiego z 1 normą
//
/**
* @author Paweł Lodzik & Tomasz Cwik
*/

#include "stdafx.h"

using namespace std;

#define typ float //Użyty typ zmiennoprzecinkowy jako typ elememntów wektorów, macierzy
#define MAXN 200; //Maksymalny rozmiar macierzy, jaki może zostać wczytany z pliku

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


//Funkcja realizująca kolejne iteracje 
void funkcjaC() {

	typ norma = 0.0;
	typ maksimum = 0.0;
	typ pom = 0.0;

	//Wyznaczanie przyblizenia zerowego	
	for (int i = 1; i < n + 1; i++) {
		//Przepisujemy wektor Beta jako aktualne przyblizenie
		Xk1[i] = Beta[i];
	}
	//Wyznaczanie kolejnych przybliżeń
	iter++;
	do {
		
		
	} while (iter <= MLI && norma >= epsilon);
}



int main()
{
	if (funkcjaA()) { //Przypadek pomyślnego wczytania danych
		if (funkcjaB()) //Pomyślnie obliczono macierz alfa i wektor beta
		{

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

