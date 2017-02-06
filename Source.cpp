#include <iostream>
#include<fstream>
#include <string>

using namespace std;

typedef struct ruch {
	
	int x;
	int y;

};

int dynam_kolumna, dynam_wiersz;


void wypelnij(int **szachownica, string nazwa);
bool sprawdzCzyMozliwe(ruch nast, int **szachownica);
bool znajdzMiejsce(int **szachownica, ruch ruch_K[], ruch aktualny, int liczba);
void moveChess(int **szachownica, string nazwa);
void wyczysc(int ** szachownica);
void noarg();
void nzapis();



//główna funkcja
int main(int argc, char* argv[]) {
//fragment odpowiadający za argumenty
//------------------------------------------------------
	for (int g = 1; g<5; g++)
	{
		if (argv[g] == nullptr)
			noarg();
	}
	string przel = argv[1];
	string nazwa = argv[2];
	string przel2 = argv[3];
	string liczba = argv[4];
	char* str = argv[4];
	int i;
	sscanf_s(str, "%d", &i);

	if (przel == "-o")
	{
		string text = ".txt";
		size_t found = nazwa.find(text);
		if (found != std::string::npos)
		{
			if (przel2 == "-n")
			{
				for (char znak : liczba)
				{
					if (znak < '0' || znak > '9')
					{
						cout << "Ostatni argument musi byc cyfra" << endl; exit(0);
					}
				}
//koniec 				
//---------------------------------------------------------

					//właściwy main

					dynam_wiersz = i;
					dynam_kolumna = i;

					//tworzenie tablicy
					int **szachownica = new int *[dynam_wiersz];

					for (size_t wiersz = 0; wiersz < dynam_wiersz; wiersz++) {

						szachownica[wiersz] = new int[dynam_kolumna];

						for (size_t kolumna = 0; kolumna < dynam_kolumna; kolumna++) {
							szachownica[wiersz][kolumna] = 0;
						}
					}


					moveChess(szachownica, nazwa);

					cout << "\n";

					system("PAUSE");


					//czyszczenie pamieci
					void wyczysc(int ** szachownica);

//dalsza czsc odpowiadajaca za argumenty
//---------------------------------------------------

			}
			else
			{
				nzapis();
			}
		}
		else { nzapis(); }
	}
	else { nzapis(); }
//----------------------------------------------------		
	return 0;
}





void moveChess(int **szachownica, string nazwa) {

	//ruchy jakimi dysponuje skoczek
	ruch ruch_K[8] = { { 2,1 },{ 1,2 },{ -1,2 },{ -2,1 },
	{ -2,-1 },{ -1,-2 },{ 1,-2 },{ 2,-1 } };

	//punkt startowy
	ruch aktualny = { 0,0 };

	if (znajdzMiejsce(szachownica, ruch_K, aktualny, 0) == false) {
		cout << "\nProblem skoczka nie wystepuje dla punktu startowego (0,0). Szachownica musi byc co najmniej 7x7!";
	}

	else {
		cout << "\nProblem skoczka wystepuje \n";
		wypelnij(szachownica, nazwa);
	}

}





bool znajdzMiejsce(int **szachownica, ruch ruch_K[], ruch aktualny, int liczba) {

	ruch nast;

	if (liczba == dynam_kolumna*dynam_wiersz - 1) {
		// Problem skoczka jest rozwiazany co oznacza,
		// ze wszystkie pola zostaly odwiedzone dokladnie jeden raz
		return true;
	}

	for (int i = 0; i < dynam_kolumna; i++) {
		nast.x = aktualny.x + ruch_K[i].x;
		nast.y = aktualny.y + ruch_K[i].y;

		if (sprawdzCzyMozliwe(nast, szachownica)) {
			szachownica[nast.x][nast.y] = liczba + 1;

			if (znajdzMiejsce(szachownica, ruch_K, nast, liczba + 1) == true) {
				return true;
			}
			else {
				szachownica[nast.x][nast.y] = 0;
			}
		}
	}


	return false;
}



bool sprawdzCzyMozliwe(ruch nast, int **szachownica) {

	int i = nast.x;
	int j = nast.y;

	if ((i >= 0 && i < dynam_kolumna) && (j >= 0 && j < dynam_kolumna) && (szachownica[i][j] == 0))
	{
		return true;
	}
	return false;
}


void wypelnij(int **szachownica, string nazwa) {

	fstream plik;
	plik.open(nazwa.c_str(), ios::trunc | ios::out);
	if (plik.good() == true)
	{
		cout << "Zapis poprawny!" << endl;
		for (size_t wiersz = 0; wiersz < dynam_wiersz; wiersz++,cout<<endl) {
			for (size_t kolumna = 0; kolumna < dynam_kolumna; kolumna++) {
			
				plik << szachownica[wiersz][kolumna]<<"\t"; //wpisywanie wyniku do pliku
			}
			plik << endl;
		}
		plik.close();
	}
	else cout << "Blad zapisu!" << endl;
	
}


void wyczysc(int ** szachownica) {
	
	for (size_t wiersz = 0; wiersz < dynam_wiersz; wiersz++)
		delete[] szachownica[wiersz];
	delete[] szachownica; 
	szachownica = NULL;

}

void noarg()
{
	cout << "Uzupelnij wymagane argumenty" << endl;
	cout << "Sprobuj:" << "nazwa_programu.exe -o nazwapliku.txt -n liczba" << endl;
	exit(0);
}
void nzapis()
{
	cout << "Blad zapisu" << endl;
	cout << "Sprobuj:" << "nazwa_programu.exe -o nazwapliku.txt -n liczba" << endl;
	exit(0);
}

