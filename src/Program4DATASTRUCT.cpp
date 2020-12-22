/*
Student Name : Rey Baltar
Student ID : hrb217
Compiler used : Eclipse using MinGW
Program description:
	This program allows the user to interact with a command line interface so that the user
	can add and make modifications to a patient queue simulator for a
	hospital.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Heap.h"
using namespace std;

string breakString(string word, string cmd){
//"breaks" the second string by the length of the first string and returns new broken string

	//initialize variables
	string hanger;
	int value1 = word.length()+1; //incremented by 1 to include the space in the second word
	int value2 = cmd.length();

	//begins adding characters after the space after the first word.
	for(int i = value1; i < value2; i++){
		hanger += cmd[i];
	}

	return hanger;
}


string buildString(string word, string cmd){
//simply adds the second string to the first string and returns the new string

	// adds a space between words and increments
	word += " ";
	word += cmd;

	return word;
}

void parse(string& New, string Old, string& LS, string FS){
	//rebuilds the string to a stored variable and breaks the full state_ment so that 'new'
	//gets the remaining text starting with the desired word
	LS = buildString(LS, Old);
	New = breakString(LS, FS);
}

int main() {

	//initialize variables
	string command, word1, word2, leftSide, full_statement; //user input variables
	string admit_cmd, admit_w1, admit_w2, admit_ls, admit_full; //admit input variables
	string pri[5] = {"code", "critical", "urgent", "non-urgent", "ambulatory"};
	ifstream itext;
	bool run = true;
	Heap list;
	int ticket = 0;

	//introduce program
	cout <<"NOTE: for the 'load' command, include the '.txt' after the file name" << endl<< endl;

	//enters parse loop
	while(run){


		/*
		 * checks whether or not a file is open so that the program knows
		 * whether to prompt the user for a command line or automatically
		 * parse the next line of the file
		 */
		if(!itext.is_open()){
			cout << "Command Line: ";
			getline(cin, command);

		}else{
			getline(itext, command);
		}

		//stores the full command statement
		full_statement = command;
		stringstream ss(command);

		// redefines command as the first word in full statement
		getline(ss, command, ' ');

		// stores words that are "broken" from strings
		leftSide = command;

		// assigns object1 to a modified full_statement with 'command' removed
		word1 = breakString(command, full_statement);

		//and define 'object1' as the second word of the full statement and
		getline(ss, word1, ' ');

		//for the following operations the remaining statement from the user will be parsed
		parse(word2, word1, leftSide, full_statement);
		getline(ss, word2, ' ');

		//*** NOW WE ENTER THE IF STATEMENTS *** //

		if(command == "exit"){
			//exits the program
			break;


		}else if(command == "display"){
			//check if the heap is empty and informs if it is. otherwise displays the
			//root contents
			if(list.size() <1){

				cout << "List is empty. Display failed" << endl;
			}else{
				cout << endl;
				cout <<"CURRENT"<<endl;
				list.peak(cout);
			}

		}else if(command== "load"){
			//opens a .txt file and obtains its text
			itext.open( word1 );

		}else if(command == "next"){
			//checks if the heap is empty, otherwise delete the current patient
			// and informs on its removal

			if(list.size() <1){
				cout << "list is empty. Next failed" << endl;
			}else{

				Patient temp = list.pop();
				cout << temp.first + " " + temp.last + " removed." << endl;
			}
		}else if( command == "admit"){
			//initialize variables
			bool admit = true;
			Patient* admit_ptr;

			//check if patient has a full name, otherwise cancels the
			//admit getline loop
			if(word1 =="" || word2 == ""){
				cout << "invalid name" << endl;
				admit =false;

			}else{
				//updates the ticket counter and creates a new data set
				//for patient and displays its default contents
				ticket += 1;
				admit_ptr = new Patient(word1, word2, ticket);
				cout <<endl;
				cout << "Creating patient record for " + word2 + ", "+word1<< endl;
				cout << "Priority: " + admit_ptr->get_priority() << endl;
				cout << "Ticket: " << ticket << endl;
				cout << "Please add description of complaint and any recorded symptoms." << endl;
			}

			//admit getline loop
			while(admit){
				/*
				 * checks whether or not a file is open so that the program knows
				 * whether to prompt the user for a command line or automatically
				 * parse the next line of the file
				 */
				if(!itext.is_open()){
					cout << "admit Line: ";
					getline(cin, admit_cmd);

				}else{
					getline(itext, admit_cmd);
				}

				//stores the full command statement
				admit_full = admit_cmd;
				stringstream sa(admit_cmd);

				// redefines command as the first word in full statement
				getline(sa, admit_cmd, ' ');

				// stores words that are "broken" from strings
				admit_ls = admit_cmd;

				// assigns object1 to a modified full_statement with 'command' removed
				admit_w1 = breakString(admit_cmd, admit_full);

				//and define 'object1' as the second word of the full statement and
				getline(sa, admit_w1, ' ');

				//for the following operations the remaining statement from the user will be parsed
				parse(admit_w2, admit_w1, admit_ls, admit_full);
				getline(sa, admit_w2);

				/// if statements////

				if(admit_cmd == "timda"){
					//inserts the patient into the heap and signal
					//the loop to exit
					list.insert(*admit_ptr);
					delete admit_ptr;
					admit = false;

				}else if(admit_cmd == "set"){

					//check if the complaint or priority needs to be set, otherwise inform user of failure
					if(admit_w1 == "complaint"){
						admit_ptr->set_complaint(admit_w2);
						cout << "complaint set" << endl;

					}else if(admit_w1 == "priority"){
						//check if the priority level exist in the priority list
						bool check = false;
						for(int i = 0; i < 5; i++){
							if(pri[i] == admit_w2){
								check = true;
							}
						}
						//sets the priority level if it's valid
						if(check){
							admit_ptr->set_priority(admit_w2);
							cout << "Priority set to " + admit_w2<<endl;
						}
						else{cout << "set failed - invalid priority level" << endl;}

					}else{cout << "set failed - check what is being 'set'." << endl;}

				}else if(admit_cmd == "add" and admit_w1 == "symptom"){
					//adds a symptom to the patient
					admit_ptr->symptoms.push_back(admit_w2);
					cout<<admit_w2 + " added as symptom"<<endl;

				}else{
					//informs on non-existent command
					cout << "invalid admit command" << endl;
				}

				//checks if the test file is being processed and if it has reached its end
				if(itext.is_open() and itext.eof()){
					//closes text file and returns to the user interface command line
					itext.close();
				}
				//// end of admit loop ////
			}

		}else{
			//informs of non-existent command
			cout << "invalid command" << endl;
		}
		//checks if the test file is being processed and if it has reached its end
		if(itext.is_open() and itext.eof()){
			//closes text file and returns to the user interface command line
			itext.close();
		}
		//end of loop//
	}

	return 0;
}
