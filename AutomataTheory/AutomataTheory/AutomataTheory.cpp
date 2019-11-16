// AutomataTheory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int numStates = 0;

class FiniteAutomata {
public:
	int stateCount;
	vector<State> states;
    vector<State> finalStates;

};

class State {
public:
	int stateName;
	vector<string> transition; //a b b       (if it has the same character twice, it's a NFA, else DFA)
	vector<State> transitionState; // 1 2 1     (therefore b -> 1 or 2)

};

int main()
{
	FiniteAutomata NFA;
	FiniteAutomata DFA;
	State tempState; //temp state to intiaizing variables

	//CONFIGURABLES
	int stateCount = 3;
	int charCount = 2;
	int finalStateCount = 1;

	//3 (0, 1, 2)	//THREE STATES
	//2 (a, b)		//2 CHARACTERS	
	//1 (2)			//1 FINAL STATE
	//
	//0 a(0,1) b(0)	//STATE 0, TRANSITION A -> Q0, OR Q1, TRANSITION B -> Q0
	//1 b(2)		//STATE 1, TRANSITION B -> Q2
	//2				//STATE 2, NO TRANSITION
	//

	//intializing 3 states
	int i = 0;
	for (i = 0; i < stateCount; i++) {
		State newState;
		newState.stateName = i;
		NFA.states.push_back(newState);
	}
	NFA.stateCount = i;
	NFA.finalStates.push_back(NFA.states.at(2));

	//state 0 transitions
	tempState = NFA.states.at(0);
	tempState.transition.push_back("a");
	tempState.transition.push_back("a");
	tempState.transition.push_back("b");
	tempState.transitionState.push_back(NFA.states.at(0));
	tempState.transitionState.push_back(NFA.states.at(1));
	tempState.transitionState.push_back(NFA.states.at(0)); //This causes it to be NFA

	//state 1 transitions
	tempState = NFA.states.at(1);
	tempState.transition.push_back("b");
	tempState.transitionState.push_back(NFA.states.at(2));
	
	//state 2 transitions
	tempState = NFA.states.at(2);
	//Bitch is empty






	


    cout << "Hello World!\n";


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
