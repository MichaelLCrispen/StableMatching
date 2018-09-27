#include <iostream>
#include <fstream>
#include <string>
#include <vld.h>
#include "LinkedList.h"
using namespace std;

/****************************************************************************************************************/
/*										The Stable Matching Program												*/
/*												Developed by													*/
/*											Michael		Crispen													*/
/*																												*/
/****************************************************************************************************************/


//Global Enumerations
enum menName { VICTOR = 0, WYATT = 1, XAVIER = 2, YANCEY = 3, ZEUS = 4 };
enum womanName { AMY = 0, BERTHA = 1, CLARE = 2, DIANE = 3, ERIKA = 4 };

//Constant number in both lists
const int n = 5; //Number of men & Women


//Function Declerations
void StandardInitializePreferances(int manPref[n][n], int womanPref[n][n]);
void ReadPreferancesFromFile(int manPref[n][n], int womanPref[n][n]);
void StableMatch(int manPref[n][n], int womanPref[n][n], int matches[n]);
void PrintMatches(int matches[n]);

int main() {
	int manPref[n][n];
	int womanPref[n][n];
	int matches[n];
	
	try {
		//StandardInitializePreferances(manPref, womanPref);
		ReadPreferancesFromFile(manPref, womanPref);
		StableMatch(manPref, womanPref, matches);
		PrintMatches(matches);
	}

	catch (string n) {

		cout << endl << endl;
		cout << "Program Shutting down due to error: " << n << endl << endl;
		system("pause");
		return 1;
	}

	cout << endl << endl;
	system("pause");
	return 0;
}



void StandardInitializePreferances(int manPref[n][n], int womanPref[n][n]) {
	//This function is a hardcoded preferance initializer so to test with a standard input.
	//We use names in this as it is easier to read than numbering each man and woman.

	//Women are numbers 0 to N-1, Men are numbered 0 to N-1
	//Amy	  W0
	womanPref[0][0] = ZEUS;
	womanPref[0][1] = VICTOR;
	womanPref[0][2] = WYATT;
	womanPref[0][3] = YANCEY;
	womanPref[0][4] = XAVIER;

	//Bertha  W1
	womanPref[1][0] = XAVIER;
	womanPref[1][1] = WYATT;
	womanPref[1][2] = YANCEY;
	womanPref[1][3] = VICTOR;
	womanPref[1][4] = ZEUS;

	//Clare	  W2
	womanPref[2][0] = WYATT;
	womanPref[2][1] = XAVIER;
	womanPref[2][2] = YANCEY;
	womanPref[2][3] = ZEUS;
	womanPref[2][4] = VICTOR;

	//Diane   W3
	womanPref[3][0] = VICTOR;
	womanPref[3][1] = ZEUS;
	womanPref[3][2] = YANCEY;
	womanPref[3][3] = XAVIER;
	womanPref[3][4] = WYATT;

	//Erika	  W4
	womanPref[4][0] = WYATT;
	womanPref[4][1] = YANCEY;
	womanPref[4][2] = ZEUS;
	womanPref[4][3] = XAVIER;
	womanPref[4][4] = VICTOR;


	//Victor M0
	manPref[0][0] = BERTHA;
	manPref[0][1] = AMY;
	manPref[0][2] = DIANE;
	manPref[0][3] = ERIKA;
	manPref[0][4] = CLARE;

	//Wyatt  M1
	manPref[1][0] = BERTHA;
	manPref[1][1] = AMY;
	manPref[1][2] = DIANE;
	manPref[1][3] = ERIKA;
	manPref[1][4] = CLARE;

	//Xavier M2
	manPref[2][0] = BERTHA;
	manPref[2][1] = ERIKA;
	manPref[2][2] = CLARE;
	manPref[2][3] = DIANE;
	manPref[2][4] = AMY;

	//Yancey M3
	manPref[3][0] = AMY;
	manPref[3][1] = DIANE;
	manPref[3][2] = CLARE;
	manPref[3][3] = BERTHA;
	manPref[3][4] = ERIKA;

	//Zeus   M4
	manPref[4][0] = BERTHA;
	manPref[4][1] = DIANE;
	manPref[4][2] = AMY;
	manPref[4][3] = ERIKA;
	manPref[4][4] = CLARE;

}

void ReadPreferancesFromFile(int manPref[n][n], int womanPref[n][n]) {
	//Read in preferances from file.
	//open file
	//Read in n lines of preferances (This will be the womans preferances)
	//Read in n lines of preferances (This will be the mans preferances)
	//This is always assuming that the input is the correct number of lines
	//If the file does not exist it will throw the error that the file was not found

	ifstream inFile;
	string filename;
	int temp;
	
	cout << "Please Enter The Filename You Wish To Use: ";
	cin >> filename;

	inFile.open(filename);

	if (inFile.is_open()) {
		for (int i = 0; i < n; i++) {
			//cout << endl;
			for (int j = 0; j < n; j++) {
				inFile >> temp;
				womanPref[i][j] = temp;
				//cout << temp << " " ;
			}
		}

		for (int i = 0; i < n; i++) {
			//cout << endl;
			for (int j = 0; j < n; j++) {
				inFile >> temp;
				manPref[i][j] = temp;
				//cout << temp << " ";
			}
		}
	}

	else {
		string error = "Error 404 File Not Found";
		throw(error);
	}

	return;
}

void StableMatch(int manPref[n][n], int womanPref[n][n], int matches[n]) {
	
/* 

	Men and women are represented by integers 0...n-1

	ManPref is the preference list of all men for all women.
	ManPref[m][i] =  w is at ith position in the preference list of m

	WomanPref is the preference list of all women for all men.
	WomanPref[w][i] =  m is at ith position in the preference list of w

	Ranking gives the ranking of each woman in the preference list of each man
	Ranking[w][m] =  manPref[w][i] = m

	Current gives the current engagement of each man
	Current[w] =  m is currently engaged to w

	Next gives the index of next man to propose to in the preference list of each woman
	Next[w] =  w has proposed to all m s.t. womanPref[w][j] = m for j = 1...i-1 but not womanPref[w][i]

	Steps
		1. Identify Free Woman
		2. For a woman W identify the highest-ranked man to whom hasnt proposed
		3. For a man M, we need to decide if M is currently engaged, if he is, identify current partner
		4. For a man M and two Women W and W', we need to be able to decide (In constant time), whether W or W' is preferred by M

Start by creating n x n array ranking where Ranking [M,W] contains the rank of woman W in sorted order of M's preferances.
*/
	LinkedList freeWoman;
	int Ranking[n][n], Next[n], Current[n];
	int m , w; //Man and woman working with

	//Init step
	
	for (int i = 0; i < n; i++){

		Next[i] = 0;
		Current[i] = -1;
		freeWoman.Push(i);

		for (int j = 0; j < n; j++)
			Ranking[i][manPref[i][j]] = j +1;
	}

	//BLAB
	for (int i = 0; i < n; i++) {
		cout << endl << "Woman " << i << "'s Preferance List: ";
		for (int y = 0; y < n; y++) {
			cout << womanPref[i][y] << " ";
		}
	}

	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << endl << "Man " << i << "'s   Preferance List: ";
		for (int y = 0; y < n; y++) {
			cout << manPref[i][y] << " ";
		}
	}
	cout << endl << endl;

	cout << "Ranking List: ";
	for (int i = 0; i < n; i++) {
		cout << endl;
		for (int j = 0; j < n; j++)
			cout << Ranking[i][j] << " ";
	}


	cout << endl << endl << "Next List: " << endl;
	for(int i = 0; i < n; i++){
		cout << Next[i] << " ";
	}

	cout << endl << endl << "Current List: " << endl;
	for (int i = 0; i < n; i++) {
		cout << Current[i] << " ";
	}

	cout << endl << endl << "freeWoman LinkedList: " << endl;
	freeWoman.PrintList();
	cout << endl << endl;
	//End Blab
	//End Initialization


	//Algorithm
	cout << "Proposals: " << endl;
	while (!freeWoman.isEmpty()) {
		w = freeWoman.Front();
		m = womanPref[w][Next[w]++];
		cout << "Next: " << Next[w] << endl; 
		cout << w << " Proposes to " << m << endl;
		
		if (Current[m] == -1) {
			cout << w <<  " Married unmarried man " << m << endl;
			Current[m] = w;
			freeWoman.Pop();
			
		}

		cout << "Checking if " << w << " " << m << " is better than " << w << "  " << Current[m] << endl;

		if (Ranking[Current[m]][m] < Ranking[w][m]) {
			cout << "This woman is better for the man.. Replacing " << endl;
			freeWoman.Pop();
			freeWoman.Push(Current[m]);
			Current[m] = w;
		}

		cout << endl << endl << endl;
	}
	

	cout << endl << endl;
	for(int i = 0; i < n; i ++)
	matches[i] = Current[i];

	return;

}

void PrintMatches(int matches[n]) {
	//Matches are printed to the screen in the form (w,m)

	for (int i = 0; i < n; i++) {
		//cout << i << "Has Married " << Current[m] << endl;
		cout << "( " << matches[i] << ", " << i << " )" << endl;
		}

		cout << endl;

return;
}