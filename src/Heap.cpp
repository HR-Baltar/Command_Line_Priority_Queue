/*
Student Name : Rey Baltar
Student ID : hrb217
Compiler used : Eclipse using MinGW
Program description:
	This program allows the user to interact with a command line interface so that the user
	can add and make modifications to a patient queue simulator for a
	hospital.
*/

#include "Heap.h"
//Heap methods

void Heap::peak(ostream&os){
	//display patient at root
	os << array[0];
}

Patient Heap::pop(){
	//initialize variables
	int trueIdx = 0; //forces the loop to start at the root
	bool satisfy = false; // loop variable
	int idx = array.size() -1; //the last index
	Patient ret;

	//ret gets the first index in the vector and then is either
	//deleted and returned if the heap contains only 1 patient
	ret = array[0];
	if(idx == 0){
		array.pop_back();
		return ret;
	}

	//or swap the first and last patient and updates the last index
	array[0] = array[idx];
	array.pop_back();
	idx -= 1; //the last index in the vector

	//enters a loop to satisfy the heap order.
	while(!satisfy){
		//assign left and right child of current index
		int left = 2*(trueIdx)+1;
		int right = 2*(trueIdx)+2;
		int select;

		//check if a right and left child exist and then breaks the loop if it does. (leaf)
		if(left > idx && right > idx){
			break;

		}else if(left > idx){ right = left;} //checks there is only a left child then assign right to left as the same integer

		//check if the left child is less then the right child and assigns 'select' to the smallest value.
		if(array[left] < array[right]){select = left;}
		else{select = right;}

		//check if the current node (or index) is less then the selected child and signals the loop to end if it does
		if(array[trueIdx] < array[select]){
			satisfy = true;

		}else{
			//otherwise swap the node with its smallest child
			Patient key = array[trueIdx];
			array[trueIdx] = array[select];
			array[select] = key;
			trueIdx = select;
		}
	}
	//returns the deleted patient after the loop ends
	return ret;
}

void Heap::insert(Patient P){

	bool satisfy = false; //loop singal
	int index = array.size(); //what will be the last index

	//adds the patient
	array.push_back(P);

	//satisfy the heap min property
	while(!satisfy){

		//pointers for swapping
		Patient	*key, *parent;
		key = &P;//assigns to the address of the new patient

		//check if this new patient is now the only patient in the heap and ends the loop
		if(&array.front() == key){
			break;
		}


		//mathematically finds the parent and checks if the parent is greater then the node
		parent = &array[(index-1)/2];
		if(P < *parent){
			//swap the parent and node
			array[index] = *parent;
			array[(index-1)/2] = *key;
			index = (index-1)/2;
		}else{
			//signal the loop to end
			satisfy = true;
		}

	}
}

int Heap::size(){
	return array.size();
}

//Patient methods

string Patient::get_complaint() const{
	return complaint;
}
string Patient::get_priority() const{
	return priority;
}

void Patient::set_priority(string level){
	priority = level;
}

void Patient::set_complaint(string comp){
	complaint = comp;
}

bool Patient::operator<(const Patient&P){
	//gets the priority of the patients being compared
	string level1 = get_priority();
	string level2 = P.get_priority();
	string arr[] = {level1, level2};
	int nums[2];

	//each patient will be assigned a number based on its level.
	for(int i = 0; i <= 2; i++){
		//simultaneously compares the level with values
		string temp = arr[i];
		if(temp == "code"){ nums[i] = 1;}
		if(temp == "critical"){ nums[i] = 2;}
		if(temp == "urgent"){ nums[i] = 3;}
		if(temp == "non-urgent"){ nums[i] = 4;}
		if(temp == "ambulatory"){ nums[i] = 5;}
	}

	//compares the two levels
	int x = nums[0];
	int y = nums[1];
	if(x == y){
		//since they are the same, compare ticket numbers
		if(ticket < P.ticket){return true;}
		else{return false;}

	}else if(x < y){return true;}//this means the comparison is true

	return false;
}

ostream & operator<<(ostream & os, Patient&rhs){
	//outputs the contents of the patient
	os << rhs.last + ", " + rhs.first << endl;
	os << "Priority: " + rhs.get_priority() << endl;
	os << "Complaint: " + rhs.get_complaint() << endl;
	os << "Symptoms: ";
	vector<string>::iterator it;

	//check if there are any symptoms and displays them
	if(rhs.symptoms.size() == 0){
		os << "N/A" << endl;
	}else{
		for(it = rhs.symptoms.begin(); it != rhs.symptoms.end(); ++it){
			os << *it << " ";
		}
		os<<endl;
	}
	os << endl;
	return os;
}
