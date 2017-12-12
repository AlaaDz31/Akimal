#include <iostream>
#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include "TableSets.h"
#include "..\Utils\basics.h"
using namespace std;

#ifndef Graphical
#define Graphical

const int  DEF_W = 55;  //larghezza di default delle tabelle

//Prototipi per utilizzo più veloce (solo completi)
/*
void Cgoto(short x, short y);																	//Spostamento cursore						(x, y)		
int GetY();																						//Ottiene posizione Y nella console			
void DrawTop(TableSet set = DEFAULT_SET, int len = DEF_W);										//Disegna linea superiore					(set, len)
void DrawBottom(TableSet set = DEFAULT_SET, int len = DEF_W);									//Disegna fine								(set, len)
void DrawSep(TableSet set = DEFAULT_SET, int len = DEF_W);										//Disegna separatore						(set, len)
void DrawLimits(TableSet set = DEFAULT_SET, int len = DEF_W);									//Disegna Linee verticali esterne			(set, len)
void DrawTab(int lines, TableSet set = DEFAULT_SET, int len = DEF_W);							//Disegna tutti i bordi						(set, len)
void CleanLine(TableSet set = DEFAULT_SET, int len = DEF_W);									//Pulisce linea								(set, len)
void Intex(string mex, bool isEnd = false, TableSet set = DEFAULT_SET, int len = DEF_W);		//Disegna intestazione						(mex, isEnd, set, len)
void CleanIntex(TableSet set = DEFAULT_SET, int len = DEF_W);									//Pulisce Intestazione						(set, len)
void Print(string mex, TableSet set = DEFAULT_SET, int len = DEF_W);							//Output per la tabella						(mex, set, len)
void GPause(bool isEnd = false, TableSet set = DEFAULT_SET, int len = DEF_W);					//Pausa per tabella							(isEnd, set, len)
int IntGIn(string mex, TableSet set = DEFAULT_SET, int len = DEF_W);							//Input (cin) per tabella					(mex, set, len)
string GGetline(string mex, TableSet set = DEFAULT_SET, int len = DEF_W);						//Input (getline) per tabella				(mex,set, len)	
int Menu(string a[], int size, TableSet set = DEFAULT_SET, int len = DEF_W);					//Menu interattivo con frecce direzionali	(a, size, set, len)
int ArrowsIntInput(string mex, int min = INT_MIN, int max = INT_MAX, bool isEnd = false, bool isSep = false, TableSet set = DEFAULT_SET, int len = DEF_W); 	//Input interattivo con frecce direzionali.  
//---------------------------------------------																													(mex, min, max, isEnd, idSep, set, len)
*/
/*
Parametri formali più usati:
-set: set di caratteri. Vedi TebleSet.h
-len: larghezza tabella
-lines: numero righe tabella
-mex: messaggio di servizio

Altri parametri:
-x, y: coordinate per console. PARTE DA 0,0!
-isEnd/isSep: se VERA l'ultima linea sarà finale anziché separatore /(vic)
-a: vettore di stringhe di orgine per menu
-size:numero elementi array ----># integ. con sizeof? rit.
-min, max: numeri minimi e massimi per inout con frecce
*/


void Cgoto(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int GetY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return -1;
	return csbi.dwCursorPosition.Y;
}

void  DrawTop(TableSet set = DEFAULT_SET, int len = DEF_W)
{
	cout << set.UP_RIGHT;
	for (int i = 0; i < len - 2; i++)
	{
		cout << set.HORIZONTAL;
	}
	cout << set.UP_LEFT << endl;
}

void  DrawBottom(TableSet set = DEFAULT_SET, int len = DEF_W)
{
	cout << set.DOWN_RIGHT;
	for (int i = 0; i < len - 2; i++)
	{
		cout << set.HORIZONTAL;
	}
	cout << set.DOWN_LEFT << endl;
}

void  DrawSep(TableSet set = DEFAULT_SET, int len = DEF_W)
{
	cout << set.SEP_RIGHT;
	for (int i = 0; i < len - 2; i++)
	{
		cout << set.HORIZONTAL;
	}
	cout << set.SEP_LEFT << endl;
}

void DrawLimits(TableSet set = DEFAULT_SET, int len = DEF_W)
{
	cout << set.VERTICAL;
	Cgoto(len - 1, GetY());
	cout << set.VERTICAL << endl;
}

void DrawTab(int lines, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	Cgoto(0, 0);
	lines -= 2;
	DrawTop(set, len);
	for (int i = 0; i < lines; i++)
	{
		DrawLimits(set, len);
	}
	DrawBottom(set, len);
	Cgoto(0, 0);
}

void CleanLine(TableSet set = DEFAULT_SET, int len = DEF_W)
{
	cout << set.VERTICAL;
	for (int i = 0; i < len - 2; i++)
	{
		cout << " ";
	}
	cout << set.VERTICAL << endl;
	Cgoto(0, GetY() - 1);
}

void Intex(string mex, bool isEnd = false, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	Cgoto(0, 0);
	DrawTop(set, len);
	cout << set.VERTICAL;
	Cgoto((len - mex.length() - 2) / 2, 1);
	cout << mex;
	Cgoto(len - 1, 1);
	cout << set.VERTICAL << endl;
	if (isEnd)
	{
		DrawBottom(set, len);
	}
	else
	{
		DrawSep(set, len);
	}
}

void CleanIntex(TableSet set = DEFAULT_SET, int len = DEF_W)
{
	Cgoto(0, 1);
	CleanLine(set, len);
}

void Print(string mex, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	cout << set.VERTICAL << mex;
	Cgoto(len - 1, GetY());
	cout << set.VERTICAL << endl;
}

void GPause(bool isEnd = false, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	int oldPos;
	cout << set.VERTICAL;
	Cgoto(len - 1, GetY());
	oldPos = GetY();
	cout << set.VERTICAL << endl;
	if (isEnd)
	{
		DrawBottom();
	}
	Cgoto(1, oldPos);
	system("PAUSE");
}

int IntGIn(string mex, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	int input, val = GetY();
	DrawLimits(set, len);
	Cgoto(len - 1, val);
	cout << set.VERTICAL << endl;
	DrawLimits(set, len);
	DrawBottom(set, len);
	Cgoto(0, val);
	cout << set.VERTICAL << mex;
	cin >> input;
	return input;
}

string GGetline(string mex, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	string input;
	int val = GetY();
	Cgoto(len - 1, val);
	cout << set.VERTICAL << endl;
	Cgoto(0, val);
	cout << set.VERTICAL << mex;
	fflush(stdin);
	getline(cin, input);
	return input;
}


int Menu(string a[], int size, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	char ret;
	fflush(stdin);
	int posY = GetY(), scelta = 1;
	for (int i = 0; i < size; i++)
	{
		cout << set.VERTICAL << "[ ] " << a[i];
		Cgoto(len - 1, GetY());
		cout << set.VERTICAL << endl;
	}
	DrawBottom(set, len);
	while (true)
	{
		Cgoto(1, posY + scelta - 1);
		cout << "[*]";
		if (GetAsyncKeyState(VK_UP) && (scelta > 1))
		{
			Cgoto(1, GetY());
			cout << "[ ]";
			scelta--;
		}
		else if (GetAsyncKeyState(VK_DOWN) && (scelta < size))
		{
			Cgoto(1, GetY());
			cout << "[ ]";
			scelta++;
		}
		ret = _getch();
		if (ret == 13)
		{
			Cgoto(0, posY + size + 1);
			return scelta;
		}
		Sleep(75);
	}
}

int ArrowsIntInput(string mex, int min = INT_MIN, int max = INT_MAX, bool isEnd = false, bool isSep = false, TableSet set = DEFAULT_SET, int len = DEF_W)
{
	_getch();
	Sleep(200);
	int pos = min, te, ol;
	string temp, num;
	char t;
	ol = GetY();
	if (isEnd)
		DrawBottom(set, len);
	else if (isSep)
		DrawSep(set, len);
	Cgoto(0, ol);
	while (true)
	{
		Cgoto(0, GetY());
		CleanLine(set, len);
		Print(mex, set, len);
		Cgoto(mex.size(), GetY() - 1);
		cout << "    ";
		cout << pos;
		if (GetAsyncKeyState(VK_UP) && (pos <= max - 1))
		{
			pos++;
		}
		else if (GetAsyncKeyState(VK_DOWN) && (pos >= min + 1))
		{
			pos--;
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			break;
		}
		Sleep(100);
	}
	return pos;
}

void Graph(int x[], int y[], GraphSet set = D_GRAPH)
{
	//funzione da sviluppare
}


#endif
