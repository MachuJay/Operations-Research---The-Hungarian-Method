#include <iomanip>
#include <iostream>
using namespace std;
// User-defined Functions Prototypes
int matrixzerocount(bool (&zeromatrix)[9][9], int matrixsize);
void header(), pauseheader();
void createzeromatrix(bool (&zeromatrix)[9][9], int (&matrix)[9][9], int matrixsize);
void rowzerocount(bool (&zeromatrix)[9][9], int (&zerocount)[2][9], int matrixsize);
void colzerocount(bool (&zeromatrix)[9][9], int (&zerocount)[2][9], int matrixsize);
void matrixdisplay(int (&matrix)[9][9],bool (&zeromatrix)[9][9], int, bool (&tick)[2][9], int (&mark)[9][9], bool, bool, bool, bool);
// Main Method
int main(){
	// cmd Console Recoloration
	system("COLOR f0");
	// Variables Initialization
	int matrixsize, numvalue, salary[9][9], replicate[9][9], zerocount[2][9], mark[9][9];;
	bool zeromatrix[9][9], tick[2][9];
	// Program Start
	for (int programinstance=1; ; programinstance++){
		// Data Capture: Employees and Jobs Count
		header();
		do{
			if (cin.fail()){
				cin.clear();
				cin.ignore(100,'\n');
			}
			cout << " Enter the number of open jobs: ";
			cin >> numvalue;
		}while(cin.fail() || numvalue < 2 || numvalue > 9);
		matrixsize = numvalue;
		// Data Capture: Salary Values
		cout << endl;
		for (int x=0; x<matrixsize; x++){
			cout << "   Applicant 0" << x+1 << endl;
			for (int y=0; y<matrixsize; y++){
				do{
					if (cin.fail()){
						cin.clear();
						cin.ignore(100,'\n');
					}
					if (y == 0){cout << " Candidate's Expected Salary for ";}
					else {cout << "                                 ";}
					cout << "Job #" << y+1 << ": ";
					cin >> numvalue;
				}while(cin.fail() || numvalue < 0 || numvalue >= 1000000);
				salary[x][y] = numvalue;
			}
			cout << endl;
		}
		pauseheader();
		system("pause");
		system("cls");
		// Replicate Matrix
		for (int x=0; x<9; x++){
			for (int y=0; y<9; y++){
				replicate[x][y] = salary[x][y];
			}
		}
		// Algorithm Simulation Start
		cout << endl
			<< "     " << char(210) << char(196) << char(196) << char(216) << "          "
			<< char(216) << char(196) << char(196) << char(196) << char(196) << char(196) << char(183) << endl
			<< "     " << char(206) << " Algorithm's Steps " << char(206) << endl
			<< "     " << char(211) << char(196) << char(196) << char(196) << char(196) << char(196) << char(216)
			<< "          " << char(216) << char(196) << char(196) << char(208) << endl;
		// Hungarian Algorithm Flow: Step 1
		cout << endl
			<< char(196) << char (216) << char(196) << "\n  STEP 1\n" << char(196) << char (216) << char(196)
			<< "\n  Arrange the costs in a squared matrix.\n\n";
		matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,false,false,false);
		pauseheader();
		system("pause");
		// Hungarian Algorithm Flow: Step 2
		for (int x=0; x<matrixsize; x++){
			// Retrieve Row's Smallest Value
			numvalue = replicate[x][0];
			for (int y=1; y<matrixsize; y++){
				if (replicate[x][y] < numvalue){
					numvalue = replicate[x][y];
				}
			}
			// Subtract Row's Smallest Value from Each Row Element
			for (int y=0; y<matrixsize; y++){
				replicate[x][y] -= numvalue;
			}
		}
		cout << endl << endl << endl
			<< char(196) << char (216) << char(196)	<< "\n  STEP 2\n" << char(196) << char (216) << char(196)
			<< "\n  Reduce all rows by the least value of that row to get at least one 0 in every row.\n\n";
		matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,false,false,false);
		pauseheader();
		system("pause");
		// Hungarian Method: Step 3
		for (int x=0; x<matrixsize; x++){
			// Retrieve Column's Smallest Value
			numvalue = replicate[0][x];
			for (int y=1; y<matrixsize; y++){
				if (replicate[y][x] < numvalue){
					numvalue = replicate[y][x];
				}
			}
			// Subtract Column's Smallest Value from Each Row Element
			for (int y=0; y<matrixsize; y++){
				replicate[y][x] -= numvalue;
			}
		}
		cout << endl << endl << endl
			<< char(196) << char (216) << char(196) << "\n  STEP 3\n" << char(196) << char (216) << char(196)
			<< "\n Reduce all columns by the least value of that column to get at least one 0 in every column.\n\n";
		matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,false,false,false);
		pauseheader();
		system("pause");
		// Generate Zero Matrix
		createzeromatrix(zeromatrix,replicate,matrixsize);
		// Determine Each Row's Zero Count
		rowzerocount(zeromatrix,zerocount,matrixsize);
		// Check if Exhaustive Search Would Be Used
		numvalue = 0;
		// Check if All Rows Have 2 or More Zeros
		for (int x=0; x<matrixsize; x++){
			if (zerocount[0][x] >= 2){
				numvalue++;
			}
		}
		if (numvalue == matrixsize){
			// Unsolveable Matrix
			cout << endl << endl << endl
				<< char(196) << char (216) << char(196) << "\n  CAN NOT SOLVE GIVEN MATRIX\n"
				<< char(196) << char (216) << char(196) << endl;
			matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,false,false,false);
			cout << "\n   Solution to given matrix is beyond the scope of the current program's algorithm.\n"
				<< "   Either multiple assignments combinations are currently possible or an advanced approach must be followed.\n\n";
			pauseheader();
			system("pause");
		}
		else{
			do{
				// Initialize Row and Column Zero Counts
				rowzerocount(zeromatrix,zerocount,matrixsize);
				// Initialize "ticks"
				for (int x=0; x<2; x++){
					for (int y=0; y<matrixsize; y++){
						tick[x][y] = false;
					}
				}
				// Initialize "marks"
				for (int x=0; x<matrixsize; x++){
					for (int y=0; y<matrixsize; y++){
						mark[x][y] = 1;
					}
				}
				do{
					rowzerocount(zeromatrix,zerocount,matrixsize);
					// Hungarian Method: Step 4a
					for (int x=0; x<matrixsize; x++){
						// Re-determine Each Column's Zero Count
						if (zerocount[0][x] == 1){
							for (int y=0; y<matrixsize; y++){
								if (zeromatrix[x][y] == true){
									mark[x][y] = 2;
									for (int z=0; z<matrixsize; z++){
										if (zeromatrix[z][y] == true && z != x){
											zeromatrix[z][y] = false;
											mark[z][y] = 3;
										}
									}
									break;
								}
							}
						}
					}
					
					
					//
					for (int x=0; x<2; x++){
						for (int y=0; y<matrixsize; y++){
							cout << zerocount[x][y] << " ";
						}
						cout << endl;
					}
					//
					
					
					cout << endl << endl << endl
						<< char(196) << char (216) << char(196) << "\n  STEP 4a\n" << char(196) << char (216) << char(196)
						<< "\n If a row has exactly one 0 then mark it and cross out all 0 in the corresponding column.\n\n";
					matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,false,true,false);
					pauseheader();
					system("pause");
					// Re-determine Each Column's Zero Count
					colzerocount(zeromatrix,zerocount,matrixsize);
					// Hungarian Method: Step 4b
					for (int x=0; x<matrixsize; x++){
						if (zerocount[1][x] == 1){
							for (int y=0; y<matrixsize; y++){
								if (zeromatrix[y][x] == true){
									mark[y][x] = 2;
									for (int z=0; z<matrixsize; z++){
										if (zeromatrix[y][z] == true && z != x){
											if (mark[y][z] == 1){
												mark[y][z] = 3;
											}
											zeromatrix[y][z] = false;
										}
									}
									break;
								}
							}
						}
					}
					cout << endl << endl << endl
						<< char(196) << char (216) << char(196) << "\n  STEP 4b\n" << char(196) << char (216) << char(196)
						<< "\n Then do similar procedure for all columns until all zeroes have either been marked or crossed.\n\n";
					matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,false,true,false);
					// Check if All Zeroes Have Either Been Marked or Crossed
					numvalue = 0;
					for (int x=0; x<matrixsize; x++){
						for (int y=0; y<matrixsize; y++){
							if (mark[x][y] == 1 && replicate[x][y] == 0){
								numvalue++;
							}
						}
					}
					if (numvalue != 0){
						cout << "      " << numvalue << " zero";
						if (numvalue == 1){cout <<"es";}
						cout << " remain unmarked or uncrossed.\n\n";
					}
					else{
						cout << "      No zeroes remain unmarked or uncrossed.\n\n";
					}
					pauseheader();
					system("pause");
				}while(numvalue != 0);
				// Hungarian Method: Step 4c
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 4c\n" << char(196) << char (216) << char(196);
				// Optimal Assignment is Possible
				if (matrixzerocount(zeromatrix,matrixsize) == matrixsize){
					numvalue == 1;
					break;
				}
				// Optimal Assignment is not Possible
				cout << "\n The number of assigned zeros (n=" << matrixzerocount(zeromatrix,matrixsize)
					<< ") is not enough to complete an optimal assignment.\n\n";
				pauseheader();
				system("pause");
				// Hungarian Method: Step 5
				for (int x=0; x<2; x++){
					for (int y=0; y<matrixsize; y++){
						tick[x][y] = false;
					}
				}
				// Re-determine Matrix's Row and Column Zero Count to Reflect Changes Made in Step 4b
				rowzerocount(zeromatrix,zerocount,matrixsize);
				colzerocount(zeromatrix,zerocount,matrixsize);
				// 'Tick' Unassigned Rows
				numvalue = 0;
				for (int x=0; x<matrixsize; x++){
					if (zerocount[0][x] == 0){
						numvalue++;
						tick[0][x] = true;
					}
				}
				// Check if Any Rows Were Ticked
				if (numvalue == 0){
					// All Possible Ticking is Done
					break;
				}
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 5a\n" << char(196) << char (216) << char(196)
					<< "\n Tick all the unassigned rows.\n\n";
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,true,false,true,false);
				pauseheader();
				system("pause");
				// Hungarian Method: Step 5b
				for (int x=0; x<matrixsize; x++){
					if (tick[0][x] == true){
						for (int y=0; y<matrixsize; y++){
							if (replicate[x][y] == 0){
								tick[1][y] = true;
							}
						}
					}
				}
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 5b\n" << char(196) << char (216) << char(196)
					<< "\n For every ticked row, if there is a zero then cross the corresponding column of that zero.\n\n";
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,true,false,true,false);
				pauseheader();
				system("pause");
				// Hungarian Method: Step 6
				for (int x=0; x<matrixsize; x++){
					if (tick[1][x] == true){
						for (int y=0; y<matrixsize; y++){
							if (zeromatrix[y][x] == true){
								tick[0][y] = true;
							}
						}
					}
				}
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 6\n" << char(196) << char (216) << char(196)
					<< "\n For every crossed column if there is a zero such that its row is unticked then tick it.\n\n";
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,true,false,true,false);
				pauseheader();
				system("pause");
				// Hungarian Method: Step 7
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 7\n" << char(196) << char (216) << char(196)
					<< "\n Draw lines through unticked rows and ticked columns.\n\n";
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,true,false,true,false);
				for (int x=0 ;x<matrixsize; x++){
					if (tick[0][x] == true){
						tick[0][x] = false;
					}
					else{
						tick[0][x] = true;
					}
				}
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,true,true,false);
				cout << "     These are the minimal lines required to pass every zero in the Matrix.\n\n";
				pauseheader();
				system("pause");
				// Hungarian Method: Step 8
				numvalue = 0;
				// Retrieve Highest Value from Entire "replicate" Matrix
				for (int x=0; x<matrixsize; x++){
					for (int y=0; y<matrixsize; y++){
						if (replicate[x][y] > numvalue){
							numvalue = replicate[x][y];
						}
					}
				}
				// Retrieve Smallest Value from "Untraced" Cells
				for (int x=0; x<matrixsize; x++){
					if (tick[0][x] == false){
						for (int y=0; y<matrixsize; y++){
							if (tick[1][y] == false){
								if (replicate[x][y] < numvalue){
									numvalue = replicate[x][y];
								}
							}
						}
					}
				}
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 8\n" << char(196) << char (216) << char(196)
					<< "\n Find the smallest value of the matrix such that neither it's row nor column are marked. Call it theta.\n\n";
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,true,false,false);
				cout << "\n     The theta is: " << numvalue << ".\n\n";
				pauseheader();
				system("pause");
				// Hungarian Method: Step 9
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 9\n" << char(196) << char (216) << char(196)
					<< "\n For all entries of the matrix, if there is no line then subtract theta.\n If there are 2 lines passing through then add theta.\n\n";
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,true,false,false);
				for (int x=0; x<matrixsize; x++){
					for (int y=0; y<matrixsize; y++){
						if (tick[0][x] == true || tick[1][y] == true){
							if (tick[0][x] == true && tick[1][y] == true){
								replicate[x][y] += numvalue;
							}
						}
						else{
							replicate[x][y] -= numvalue;
						}
					}
				}
				cout << "\n               Changes into:\n";
				matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,true,false,false);
				pauseheader();
				system("pause");
				// Hungarian Method: Step 10
				cout << endl << endl << endl
					<< char(196) << char (216) << char(196) << "\n  STEP 10\n" << char(196) << char (216) << char(196)
					<< "\n Repeat the algorithm starting from Step 4\n\n";
				pauseheader();
				system("pause");
				// Reset Zero Matrix
				createzeromatrix(zeromatrix,replicate,matrixsize);
			}while(true);
			// Alternate Part of Step 4c
			cout << "\n The number of assigned zeros (n=" << matrixzerocount(zeromatrix,matrixsize)
				<< ") is enough to complete an optimal assignment.\n\n";
			matrixdisplay(replicate,zeromatrix,matrixsize,tick,mark,false,false,true,false);
			pauseheader();
			system("pause");
			// Hungarian Method: Step 11
			cout << endl << endl << endl
				<< char(196) << char (216) << char(196) << "\n  STEP 11\n" << char(196) << char (216) << char(196)
				<< "\n Report all the marked zeroes. Assigning these cells will give us the least cost.\n\n"
				<< " Salary Matrix:\n";
			matrixdisplay(salary,zeromatrix,matrixsize,tick,mark,false,false,false,true);
			cout << "\n Job Assignments with Least Total Salary Cost:\n";
			numvalue = 0;
			for (int x=0; x<matrixsize; x++){
				for (int y=0; y<matrixsize; y++){
					if (zeromatrix[x][y] == true){
						cout << "    Employee #0" << x+1 << " will be assigned Job " << y+1 
						<< " with an expected salary of Php " << salary[x][y] << endl;
						numvalue += salary[x][y];
						break;
					}
				}
			}
			cout << "\n Least Total Cost: " << numvalue << endl << endl;
			pauseheader();
			system("pause");
		}
		// Confirm Program Loop Reiteration
		do{
			if (cin.fail()){
				cin.clear();
				cin.ignore(100,'\n');
			}
			system("cls");
			header();
			cout << "\t\t\t[1]:Yes [2]:Terminate\n\n Try another matrix?: ";
			cin >> numvalue;
		}while(cin.fail() || (numvalue != 1 && numvalue != 2));
		// Terminates Loop by User Input
		if (numvalue == 2){
			break;
		}
		system("cls");
	}
	return 0;
}
// User-defined Functions Definitions
void header(){
	cout << "\n      " << char(201) << "    ";
	for (int x=0; x<8; x++){
		cout << char(196);
	}
	cout << "    " << char(187)
		<< "\n       Hungarian Method"
		<< "\n      " << char(200) << "    ";
	for (int x=0; x<8; x++){
		cout << char(196);
	}
	cout << "    " << char(188) << endl << endl;
}
void pauseheader(){
	cout << char(199);
	for (int x=0; x<31 ;x++){
		cout << char(196);
	}
}
// Matrices Display Format
void matrixdisplay(int (&matrix)[9][9], bool (&zeromatrix)[9][9], int matrixsize, bool (&tick)[2][9], int (&mark)[9][9], bool ticked, bool lined, bool marked, bool final){
	cout << "      Job\n  #  ";
	for (int x=0; x<matrixsize; x++){
		cout << "   " << x+1 << "    ";
	}
	cout << "\n    " << char(201);
	for (int x=0; x<matrixsize; x++){
		cout << char(205) << char(205) << char(205);
		if (lined == true && tick[1][x] == true){cout << char(216);}
		else{cout << char(205);}
		cout << char(205) << char(205) << char(205);
		if (x+1 == matrixsize){cout << char(184);}
		else {cout << char(209);}
	}
	cout << endl;
	for (int x=0; x<matrixsize; x++){
		cout << " 0" << x+1 << " ";
		if (lined == true && tick[0][x] == true){cout << char(215);}
		else{cout << char(186);}
		for (int y=0; y<matrixsize; y++){
			if (lined == true && tick[0][x] == true){
				cout << right << setfill(char(196));
				if (marked == true && matrix[x][y] == 0 && mark[x][y] != 1){
					if (mark[x][y] == 2){
						cout << setw(5) << char(251) << " 0";
					}
					else if (mark[x][y] == 3){
						cout << setw(7) << "X";
					}
				}
				else{
					cout << setw(7) << matrix[x][y];
				}
				if (lined == true && tick[0][x] == true){cout << char(197);}
				else{cout << char(179);}
			}
			else{
				cout << right;
				if (marked == true && matrix[x][y] == 0 && mark[x][y] != 1){
					if (mark[x][y] == 2){
						cout << setw(5) << char(251) << " 0";
					}
					else if (mark[x][y] == 3){
						cout << setw(7) << "X";
					}
				}
				else{
					if (final == true && mark[x][y] == 2){
						cout << char(251 )<< setw(6) << matrix[x][y];
					}
					else{
						cout << setw(7) << matrix[x][y];
					}
				}
				cout << char(179);
			}
		}
		if (ticked == true){
			if (tick[0][x] == true){
				cout << "<";
			}
		}
		cout << "\n    ";
		if (x+1 == matrixsize){cout << char(211);}
		else {cout << char(199);}
		for (int y=0; y<matrixsize; y++){
			cout << char(196) << char(196) << char(196);
			if (lined == true && tick[1][y] == true){cout << char(197);}
			else{cout << char(196);}
			cout << char(196) << char(196) << char(196);
			if (y+1 != matrixsize){
				if (x+1 == matrixsize){cout << char(193);}
				else {cout << char(197);}
			}
		}
		if (x+1 == matrixsize){cout << char(217);}
		else {cout << char(180);}
		cout << setfill(' ');
		cout << endl;
	}
	if (ticked == true){
		cout << "    ";
		for (int y=0; y<matrixsize; y++){
			if (tick[1][y] == true){
				cout << "    ^   ";
			}
			else{
				cout << "       ";
			}
		}
	cout << endl;
	}
}
// Populates Zero Matrix
void createzeromatrix(bool (&zeromatrix)[9][9], int (&matrix)[9][9], int matrixsize){
	for (int x=0; x<matrixsize; x++){
		for (int y=0; y<matrixsize; y++){
			if (matrix[x][y] == 0){
				zeromatrix[x][y] = true;
			}
			else{
				zeromatrix[x][y] = false;
			}
		}
	}
}
// Calculates the Amount of Zeros Per Row
void rowzerocount(bool (&zeromatrix)[9][9], int (&zerocount)[2][9], int matrixsize){
	int rowcount;
	for (int x=0; x<matrixsize; x++){
		rowcount = 0;
		for (int y=0; y<matrixsize; y++){
			if (zeromatrix[x][y] == true){
				rowcount++;
			}
		}
		zerocount[0][x] = rowcount;
	}
}
// Calculates the Amount of Zeros Per Column
void colzerocount(bool (&zeromatrix)[9][9], int (&zerocount)[2][9], int matrixsize){
	int colcount;
	for (int x=0; x<matrixsize; x++){
		colcount = 0;
		for (int y=0; y<matrixsize; y++){
			if (zeromatrix[y][x] == true){
				colcount++;
			}
		}
		zerocount[1][x] = colcount;
	}
}
int matrixzerocount(bool (&zeromatrix)[9][9], int matrixsize){
	int totalzeros = 0;
	for (int x=0; x<matrixsize; x++){
		for (int y=0; y<matrixsize; y++){
			if (zeromatrix[x][y] == true){
				totalzeros++;
			}
		}
	}
	return totalzeros;
}
/* Reference Algorithm Flow Retrieved from "http://home.iitk.ac.in/~mpatel/cs300/5B/cs300_a4.pdf"
1.  Arrange the cost as described in the representation section.
2.  Reduce all rows by the least value of that row to get atleast one 0 in every row.
3.  Reduce all columns by the least value of that column to get atleast one 0 in every column.
4.  If a row has exactly one 0 then mark it and cross out all 0 in the corresponding column.
	Do this for all rows. Then do similar procedure for all column till all zeroes have either been marked or crossed.
	If the number of marked zeroes equal n then skip to step 11.
5.  Tick all the unassigned rows.  For every ticked row if there is a zero then cross the corresponding column of that zero.
6.  For every crossed column if there is a zero such that it’s row is unticked then tick it.
	Repeat steps 5 and 6 till no more ticking is possible.
7.  Cross out unticked rows.
8.  Find the smalled value of the matrix such that neither it’s row nor column are marked.  Call it theta.
9.  For all entries of the matrix , if there is no line the subtract theta .  If there is one line passing through then do nothing.
If there are 2 lines passing through then add theta.
10. Mark zeroes similar to how they were done in step 4 i.e if there is a single zero then mark it and cross all other zero in
	the corresponding column. Do this for all rows and columns. If number of marked zeroes is n the continue else go back to step 5.
11. Report all the marked zeroes. Assigning these cells will give us the least cost.
*/
