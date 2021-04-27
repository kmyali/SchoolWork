#include <iostream>
#include<string>
#include "QueueHeader.h"

void parse(string input, Queue<int>* qp);
void playWithQueue();

int main() {
	cout << "You will now enter the game: Play with Queue!!!";
	playWithQueue();
}

void playWithQueue() {
	Queue<int>* qp	= new Queue<int>();
	string input;

	while (true) {
		cout << "Enter your command as COMMAND NUMBER or enter size: ";
		cin >> input;
		parse(input, qp);
	}
}

void parse(string input, Queue<int>* qp) {
	int spacePos = input.find(" ");
	//if the user wants to display the size
	if (input == "size") {
		cout<< "\nThe size of the Queue currently is: " <<qp->size();
	}
	//if there is a space, then there is a command and a number
	else if(spacePos != string::npos) {
		string command = input.substr(0, spacePos); //creating a string with the command
		string num = input.substr(spacePos + 1, input.size() - spacePos - 1); //creating a string with the number
		//Making sure the number is a number
		if (!stoi(num)) {
			cout << "\nThe argument is not a number";
		}
		else if (command == "enqueue") {
			qp->enqueue(stoi(num));
			cout << "\nEnqueued " << stoi(num);
		}
		else if (command == "dequeue") {
			if (qp->size() == 0) {
				cout << "\nQueue is empty, unable to dequeue!";
			}
			else {
				qp->dequeue;
			}
		}
		else {
			cout << "\nCommand not recognized, please try again.";
		}
	}
}