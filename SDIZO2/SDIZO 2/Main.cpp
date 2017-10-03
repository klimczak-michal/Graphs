#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <queue>
#include <vector>
#include <list>
#include <queue>
#include <windows.h>
#define _WIN32_WINNT 0x0502

using namespace std;

const int WAGA = 8;
LARGE_INTEGER performanceCountStart, performanceCountEnd;

//			ZADANIA NA MACIERZACH //


int** nowy_pusty_graf(int rozmiar_v)
{

	int **macierz=new int *[rozmiar_v];
	for(int i=0;i<rozmiar_v;i++)
	{
		macierz[i]=new int [rozmiar_v];
		for(int z=0;z<rozmiar_v;z++)
			macierz[i][z]=0;
	}
	return macierz;
}
void wypelnij_graf(int rozmiar_v, double gestosc, int **macierz, bool skierowany)
{
	int krawedzie = ((ceil)((gestosc / 100) * rozmiar_v * (rozmiar_v - 1) * 0.5));
	int x,y,waga;

	if (skierowany == true) krawedzie *= 2;

	//spojny graf
	for (int i = 0; i < rozmiar_v-1; i++)
	{
		waga = 8;
		macierz[i][i+1] = waga;
		if (skierowany == false) macierz[i+1][i] = waga;
	}

	if (skierowany == true)
	{
		waga = 8;
		macierz[rozmiar_v - 1][0] = waga;
	}

	if (skierowany == false) krawedzie = krawedzie + 1 - rozmiar_v;
	else krawedzie = krawedzie - rozmiar_v;

	if (krawedzie >= 1)
	{
		for (int i = 0; i < krawedzie; i++)
		{
			do
			{
				x = (rand() % (rozmiar_v));
				y = (rand() % (rozmiar_v));
			} while (macierz[x][y] != 0 || x == y);
			waga = (rand() % WAGA) + 1;

			if (skierowany == false)
			{
				macierz[x][y] = waga;
				macierz[y][x] = waga;
			}
			else macierz[x][y] = waga;
		}
		//for(int i=0;i<rozmiar_v;i++)
		//macierz[i][i]=0;
	}
}
void wyswietl_graf(int rozmiar_v, int** macierz)
{
	cout<<"  \t";
	for (int i = 0; i < rozmiar_v; i++)
	{
		if (i >= 9)
			cout << i + 1;
		else
			cout << i + 1 << " ";
	}
	cout<<"\n\n";
	for(int i=0;i<rozmiar_v;i++)
	{
		cout<<i+1<<"\t";
		for(int z=0;z<rozmiar_v;z++)
		{
			
 			if(macierz[i][z]==0)
				cout<<" |";
			else
				cout<<macierz[i][z]<<"|";
 		}
		cout<<"\n";
	}
}
void wyswietl_prima(int rozmiar_v, int** macierz)
{
	if (macierz == 0) { return; }

	int waga = 0, krawedzie = 0;

	cout << "  \t";
	for (int i = 0; i<rozmiar_v; i++)
	{
		if (i >= 9)
			cout << i + 1;
		else
			cout << i + 1 << " ";
	}
	cout << "\n\n";
	for (int i = 0; i<rozmiar_v; i++)
	{
		cout << i + 1 << "\t";
		for (int z = 0; z<rozmiar_v; z++)
		{

			if (macierz[i][z] == 0)
				cout << " |";
			else
			{
				cout << macierz[i][z] << "|";
				waga += macierz[i][z];
				krawedzie++;
			}
		}
		cout << "\n";
	}
		cout << "Suma wag krawedzi(" << krawedzie/2 << ") MST: " << waga/2 << endl;
}
void wyswietl_djk(int** wynik, int rozmiar_v, int poczatek)
{
	/*for (int i = 0; i < rozmiar_v; i++)
	{
		cout << wynik[0][i] + 1 << " ";
	}

	cout << endl;
	for (int i = 0; i < rozmiar_v; i++)
	{
		cout << wynik[1][i] + 1 << " ";
	}*/

	cout << endl;

	int i = 0, tmp;

	for (i; i < rozmiar_v; i++)
	{
		if (i != poczatek)
		{
			cout << i + 1 << ": ";
			tmp = i;
			do
			{
				cout << "<-" << wynik[1][tmp] + 1;
				tmp = wynik[1][tmp];

			} while (wynik[1][tmp] != -1);
			cout << ", waga: " << wynik[0][i] << endl;
		}
		else continue;
	}
}
int** algorytm_prima_macierzowo(int **macierz, int rozmiar_v)
{
	int **wynik = nowy_pusty_graf(rozmiar_v);
	int *tab = new int[rozmiar_v]; //tablica na kolejne wierzcholki
	tab[0] = 0;
	int waga = 10, x = 0, y = 0, ile = 1, war = 0, spoj = 0, powt = 0;
	while (ile<rozmiar_v)
	{
		waga = 10;

		for (int z = 0; z<ile; z++)
		{
			for (int i = tab[z]; i<rozmiar_v; i++)
			{

				if (waga>macierz[tab[z]][i] && macierz[tab[z]][i] != 0)
				{
					waga = macierz[tab[z]][i];
					x = tab[z]; y = i;
				}
			}
		}
		for (int i = 0; i<ile; i++)
		{
			if (tab[i] == y)
				powt = 1;
		}
		if (powt == 1)
		{
			macierz[x][y] = 0;
			macierz[y][x] = 0;
			spoj++;
		}
		else
		{
			wynik[x][y] = waga;
			wynik[y][x] = waga;
			macierz[x][y] = 0;
			macierz[y][x] = 0;
			tab[ile] = y;
			ile++;
		}
		powt = 0;
		if (spoj>(rozmiar_v*rozmiar_v*rozmiar_v*rozmiar_v))
		{
			ile = rozmiar_v;
			cout << "\tgraf nie spojny";
			return macierz;
		}
	}
	return wynik;
}
int** algorytm_djk_macierzowo(int poczatek, int rozmiar_v, int** macierz)
{
	int ileS = 0, nast = -1, minWaga = WAGA * 10000;
	int poczatekS = poczatek;
	bool powt = false;
	int* s = new int[rozmiar_v];

	int **wynik = new int *[2];
	for (int i = 0; i< 2; i++)
	{
		wynik[i] = new int[rozmiar_v];
		for (int z = 0; z < rozmiar_v; z++)
		{
			if (i == 0) wynik[i][z] = WAGA * 10000;
			if (i == 1) wynik[i][z] = -1;
		}
	}
	wynik[0][poczatek] = 0;

	do
	{

		for (int i = 0; i < rozmiar_v; i++)
		{
			if (wynik[0][i] > wynik[0][poczatek] + macierz[poczatek][i] && macierz[poczatek][i] != 0)
			{
				wynik[0][i] = wynik[0][poczatek] + macierz[poczatek][i];
				wynik[1][i] = poczatek;
			}
		}

		s[ileS] = poczatek;
		ileS++;

		for (int i = 0; i < rozmiar_v; i++)
		{
			if (wynik[0][i] < minWaga)
			{

				for (int j = 0; j < ileS; j++)
				{
					if (i == s[j]) powt = true;
				}

				if (powt == false)
				{
					minWaga = wynik[0][i];
					nast = i;
				}

				powt = false;
			}
		}

		powt = false;
		poczatek = nast;
		minWaga = WAGA * 10000;
		nast = -1;


	} while (ileS < rozmiar_v);

	poczatek = poczatekS;
	return wynik;
}
			
//			OBLICZENIA NA LISCIE		//


struct Krawedz
{
	int pochodzenie;
	int p1;
	int waga;
};
struct Wierzcholek
{
	int numer;
	int waga;
};
struct PorownajWagi
{
	  bool operator ()( const Krawedz & osoba1, const Krawedz & osoba2 )
    {
        //kolejnoœæ - rosn¹co
        if( osoba1.waga > osoba2.waga ) return true;
        
        if( osoba1.waga < osoba2.waga ) return false;      
    
        return false;
    }
};
struct PorownajWierzch
{
	  bool operator ()( const Wierzcholek & osoba1, const Wierzcholek & osoba2 )
    {
        //kolejnoœæ - rosn¹co
        if( osoba1.waga > osoba2.waga ) return true;
        
        if( osoba1.waga < osoba2.waga ) return false;      
    
        return false;
    }
};
void wypelnij_graf_lista(int rozmiar,double gestosc, vector<Krawedz>* W, bool skierowany)
{
	Krawedz K;

	int** macierz = nowy_pusty_graf(rozmiar);
	wypelnij_graf(rozmiar, gestosc, macierz, skierowany);

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (macierz[i][j] != 0)
			{
				K.p1 = j; K.pochodzenie = i; K.waga = macierz[i][j];
				W[i].push_back(K);
			}
			else continue;
		}
	}



	/*Krawedz K;
	int x,waga,y;
	gestosc=(gestosc/100)*((rozmiar*(rozmiar-1))/2);	//ilosc krawedzi do zrobienia
	gestosc=ceil(gestosc);

	if (skierowany == true) gestosc *= 2;

	for(int i=1;i<rozmiar;i++)
	{
		
		x=(rand()%(i));
		waga=(rand()%(8))+1;
		
		K.p1=x; K.waga=waga; K.pochodzenie=i;
		W[i].push_back(K);								// tutaj tylko tworze graf spojny
		
		waga = (rand() % (8)) + 3;
		K.p1 = i; K.pochodzenie = x, K.waga = waga;
		W[x].push_back(K);
	}
	gestosc=gestosc-(rozmiar-1)*2;	// pozostale krawedzie do zrobienia

	int powt=0,ile=0;
	vector<Krawedz>::iterator it;
	for(int i=0;i<gestosc;i++)
	{
		do
		{
			powt=0;
			do
			{
				x=(rand()%(rozmiar));
				y=(rand()%(rozmiar));
			}while(x==y);
			

			vector<Krawedz>::iterator it;
			it=W[y].begin();
			for(it;it!=W[y].end();it++)
			{
				if ((*it).p1 == x)
				{
					powt = 1;
				}
			}

		}while(powt==1);
		waga=(rand()%(8))+1;
		K.p1=x; K.waga=waga; K.pochodzenie=y;
		W[y].push_back(K);

		if (skierowany == false)
		{
			K.p1 = y; K.pochodzenie = x;
			W[x].push_back(K);
		}
	}*/
}
void wyswietl_graf_lista(vector<Krawedz>* W, int rozmiar)
{
	cout<<"\n\n";
	vector<Krawedz>::iterator it;
	for(int i=0;i<rozmiar;i++)
	{
		cout<<i+1<<"->\t";
		it=W[i].begin();
		
		for(it ;it!=W[i].end();++it)
		{
			cout<<"|"<<(*it).p1+1<<"_"<<(*it).waga;				
		}
		cout<<"\n";
	}

}
void wyswietl_lista_prima(vector<Krawedz>* W, int rozmiar)
{
	int suma = 0, krawedzie = 0;
	cout << "\n\n";
	vector<Krawedz>::iterator it;
	for (int i = 0; i<rozmiar; i++)
	{
		cout << i + 1 << "->\t";
		it = W[i].begin();

		for (it; it != W[i].end(); ++it)
		{
			cout << "|" << (*it).p1 + 1 << "_" << (*it).waga;
			suma += (*it).waga;
			krawedzie++;
		}
		cout << "\n";
	}
	cout << "Suma wag krawedzi(" << krawedzie << ") MST: " << suma << endl;
}
void wyswietl_lista_djk(int **tab, int poczatek, int rozmiar)
{
	int i = 0, tmp;

	for (i; i < rozmiar; i++)
	{
		if (i != poczatek)
		{
			cout << i + 1 << ": ";
			tmp = i;
			do
			{
				cout << "<-" << tab[1][tmp] + 1;
				tmp = tab[1][tmp];
				
			} while (tab[1][tmp] != -1);
			cout << ", waga: " << tab[0][i] << endl;
		}
		else continue;
	}

}
vector<Krawedz>* algorytm_prima_lista(vector<Krawedz>* W, int rozmiar)
{
	priority_queue <Krawedz, vector<Krawedz>, PorownajWagi> kolejkaPriorytetowa;
	vector<Krawedz>* wynik = new vector<Krawedz>[rozmiar];
	vector<Krawedz>::iterator it;
	Krawedz K;
	int* tab = new int[rozmiar];
	for (int i = 0; i<rozmiar; i++)
		tab[i] = -1;
	int ile = 0, start = 0, liczba, y, x, powt;
	tab[start] = 9;
	do
	{
		liczba = 9999;
		powt = 0;
		it = W[start].begin();

		for (it; it != W[start].end(); ++it)
		{
			kolejkaPriorytetowa.push(*it);

		}

		W[start].clear();
		K = kolejkaPriorytetowa.top();
		kolejkaPriorytetowa.pop();
		x = start; y = K.p1;

		if (tab[y] == -1)
		{
			wynik[K.pochodzenie].push_back(K);
			start = y;
			ile++;
			tab[y] = 9;

		}


	} while (ile != rozmiar - 1);
	return wynik;
}
int** algorytm_djk_lista(int poczatek, int rozmiar, vector<Krawedz>* W)
{
	vector<Krawedz>::iterator it;
	int ileS = 0, nast = -1, minWaga = WAGA * 10000;
	int poczatekS = poczatek;
	bool powt = false;
	int* s = new int[rozmiar];

	int **wynik = new int *[2];
	for (int i = 0; i< 2; i++)
	{
		wynik[i] = new int[rozmiar];
		for (int z = 0; z < rozmiar; z++)
		{
			if (i == 0) wynik[i][z] = WAGA * 10000;
			if (i == 1) wynik[i][z] = -1;
		}
	}
	wynik[0][poczatek] = 0;

	do
	{

		it = W[poczatek].begin();
		for (it; it != W[poczatek].end(); ++it)
		{
			if (wynik[0][(*it).p1] > wynik[0][poczatek] + (*it).waga)
			{
				wynik[0][(*it).p1] = wynik[0][poczatek] + (*it).waga;
				wynik[1][(*it).p1] = poczatek;
			}
		}

		s[ileS] = poczatek;
		ileS++;

		for (int i = 0; i < rozmiar; i++)
		{
			if (wynik[0][i] < minWaga)
			{

				for (int j = 0; j < ileS; j++)
				{
					if (i == s[j]) powt = true;
				}

				if (powt == false)
				{
					minWaga = wynik[0][i];
					nast = i;
				}

				powt = false;
			}
		}

		powt = false;
		poczatek = nast;
		minWaga = WAGA * 10000;
		nast = -1;

	} while (ileS < rozmiar);

	poczatek = poczatekS;
	return wynik;
}


LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		stop;
}

int menu_2()
{
	int menu=0;
	int rozmiar,gestosc;
	int **mac, **wynik;
	double tm;
	system("cls");
		cout<<"\t SDIZO PROJEKT NR 2\n\n"
			<<"\t MENU REPREZENTACJI MACIERZOWEJ:\n\n"
			<<"\t[1]-Algorytm Prima\n"
			<<"\t[2]-Algorytm Djikstry\n"
			//<<"\t[3]-Algorytm Kruskala\n"
			<<"\t[0]-EXIT\n"
			<<"\n\nAby umozliwic obliczenia musimy stworzyc graf\n";
			cout<<"Podaj ilosc wierzcholkow: ";
			cin>>rozmiar;
			int **d;
			mac=nowy_pusty_graf(rozmiar);
			cout<<"\nPodaj gestosc: ";
			cin>>gestosc;	
			cout<<"\n\nWybierz jeden z algorytmów\n";		
		do
		{
		cin>>menu;
		switch(menu)
		{
		
		case 1:
			wypelnij_graf(rozmiar, gestosc, mac, false);
			wyswietl_graf(rozmiar, mac);
			system("Pause");
			system("cls");
			performanceCountStart = startTimer();
			wynik = algorytm_prima_macierzowo(mac, rozmiar);
			//Sleep(gestosc*10);
			performanceCountEnd = endTimer();
			if (wynik != 0) wyswietl_prima(rozmiar, wynik);
			tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / 1000;
			cout<<"Ta operacja trwala: "<<tm<<"ms\n";
			menu=0;
			break;
		case 2: 
			wypelnij_graf(rozmiar, gestosc, mac, true);
			wyswietl_graf(rozmiar, mac);
			system("Pause");
			int w;
			cout<<"\nPodaj wierzcholek: ";
			cin>>w;

			performanceCountStart = startTimer();
			d=algorytm_djk_macierzowo(w,rozmiar,mac);
			//if (gestosc <= 25 && rozmiar > 51) Sleep(gestosc*5);
			//else if (gestosc > 25 && rozmiar > 51) Sleep(gestosc);
			performanceCountEnd = endTimer();

			wyswietl_djk(d, rozmiar, w);

			tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / 1000;
			cout<<"Ta operacja trwala: "<<tm<<"ms\n";
			menu=0;
			break;
		/*case 3:
			t1=obliczSekundy(clock());
			wyswietl_graf(rozmiar,algorytm_kruskala_macierzowo(mac,rozmiar));
			t2=obliczSekundy(clock());
			cout<<"Ta operacja trwala: "<<t2-t1<<"\n";
			menu=0;
			break;*/
		}
		}while(menu!=0);
		system("Pause");
	return menu;
}
int menu_3()
{
	int menu=0;
	int rozmiar, gestosc;
	long float tm;

	system("cls");
		cout<<"\t SDIZO PROJEKT NR 2\n\n"
			<<"\t MENU REPREZENTACJI LISTOWEJ:\n\n"
			<<"\t[1]-Algorytm Prima\n"
			<<"\t[2]-Algorytm Djikstry\n"
			//<<"\t[3]-Algorytm Kruskala\n"
			<<"\t[0]-EXIT\n"
			<<"\n\nAby umozliwic obliczenia musimy stworzyc graf\n";
			cout<<"Podaj ilosc wierzcholkow: ";
			cin>>rozmiar;
			int** d;// = new int[rozmiar];
			vector<Krawedz>* tab= new vector<Krawedz> [rozmiar];
			vector<Krawedz>* wynik;
			cout<<"\nPodaj gestosc: ";
			cin>>gestosc;
			cout<<"\n\nWybierz jeden z algorytmów:\n";
		do
		{
		cin>>menu;
		switch(menu)
		{
		
		case 1:
			wypelnij_graf_lista(rozmiar, gestosc, tab, false);
			wyswietl_graf_lista(tab, rozmiar);
			system("Pause");
			system("cls");
			performanceCountStart = startTimer();
			wynik = algorytm_prima_lista(tab, rozmiar);
			performanceCountEnd = endTimer();
			if (wynik != 0) wyswietl_lista_prima(wynik, rozmiar);
			tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / 1000;
			cout<<"Ta operacja trwala: "<<tm<<"ms\n";
			menu=0;
			break;
		case 2: 
			wypelnij_graf_lista(rozmiar, gestosc, tab, true);
			wyswietl_graf_lista(tab, rozmiar);
			system("Pause");
			int w;
			cout<<"\nPodaj wierzcholek: ";
			cin>>w;
			performanceCountStart = startTimer();
			d=algorytm_djk_lista(w,rozmiar,tab);
			//if (gestosc > 50) Sleep(gestosc);
			performanceCountEnd = endTimer();
			wyswietl_lista_djk(d, w, rozmiar);
			tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart)/1000;
			cout<<"Ta operacja trwala: "<<tm<<"ms\n";
			menu=0;
			break;
		/*case 3:
			t1=obliczSekundy(clock());
			wyswietl_graf_lista(algorytm_kruskala_lista(tab,rozmiar),rozmiar);
			t2=obliczSekundy(clock());
			cout<<"Ta operacja trwala: "<<t2-t1<<"\n";
			menu=0;
			break;*/
		}
		}while(menu!=0);
		system("Pause");
	return menu;

}
int menu_1()
{
	int menu=0;
	system("cls");
		cout<<"\t SDIZO PROJEKT NR 2\n\n"
			<<"MENU:\n\n"
			<<"[1]-Reprezentacja macierzowa\n"
			<<"[2]-Reprezentacja listowa\n"
			<<"[0]-EXIT\n";
		cin>>menu;
		switch(menu)
		{
		case 1: menu_2();
			break;
		case 2: menu_3();
			break;
		}
	return menu;
}
void main()
{
	
	HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X = 150;
	sizeOfBuff.Y = 100;
	SetConsoleScreenBufferSize(buff, sizeOfBuff);

	/*
	//Macierz Prima
	mac = nowy_pusty_graf(rozmiar1);
	wypelnij_graf(rozmiar1, gestosc, mac, false);
	//wyswietl_graf(rozmiar1, mac);

	performanceCountStart = startTimer();
	wynik = algorytm_prima_macierzowo(mac, rozmiar1);
	performanceCountEnd = endTimer();
	//wyswietl_prima(rozmiar, wynik);
	tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / 1000;
	cout << tm << "ms\n";
	//system("Pause");
	
	
	//Macierz Dijkstra
	mac = nowy_pusty_graf(rozmiar2);
	wypelnij_graf(rozmiar2, gestosc, mac, true);
	//wyswietl_graf(rozmiar, mac);
	performanceCountStart = startTimer();
	d = algorytm_djk_macierzowo(w, 3, rozmiar2, mac);
	performanceCountEnd = endTimer();
	//wyswietl_djk(d, rozmiar, 0);
	tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / 1000;
	cout << "Ta operacja trwala: " << tm << "ms\n";
	
	
	//Lista Prima
	tab = new vector<Krawedz>[rozmiar1];
	wypelnij_graf_lista(rozmiar1, gestosc, tab, false);
	performanceCountStart = startTimer();
	wynikL = algorytm_prima_lista(tab, rozmiar1);
	performanceCountEnd = endTimer();
	tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / 1000;
	cout << "Ta operacja trwala: " << tm << "ms\n";

	//Lista Dijkstra
	tab = new vector<Krawedz>[rozmiar2];
	wypelnij_graf_lista(rozmiar2, gestosc, tab, false);
	performanceCountStart = startTimer();
	d = algorytm_djk_lista(w, 3, rozmiar2, tab);
	performanceCountEnd = endTimer();
	tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / 1000;
	cout << "Ta operacja trwala: " << tm << "ms\n";
	system("Pause");*/

	int menu;
	srand(time(NULL));
	do
	{
		menu=menu_1();
	}while(menu!=0);
}


