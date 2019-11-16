// AutomataTheory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;
//void calcStates(FiniteAutomata NFA, FiniteAutomata DFA, State state);

int numStates = 0;

class State {
public:
	string stateName;
	vector<string> transition; //a b b       (if it has the same character twice, it's a NFA, else DFA)
	vector<State> transitionState; // 1 2 1     (therefore b -> 1 or 2)

	State() {

	}
};

class FiniteAutomata {
public:
	int stateCount;
	vector<State> states;
    vector<State> finalStates;

	FiniteAutomata() {

	}
	void print() {
		//print out the entirety of the Automata
		
		cout << "There are " + to_string(stateCount) + " states in the automata" << endl;
		for (State x : states) {
			cout << "State " + x.stateName + " contains the following transitions: " << endl;
			for (int i = 0; i < x.transition.size(); i++) {
				
		
				cout << x.transition.at(i) + " - > " + x.transitionState.at(i).stateName << endl;
			}
			cout << "" << endl;
		}
	}
	bool isExistStateName(string x) {
		//loop through states.stateNames to see if name x exists
		//return true if it exists else false
		
		if (states.size() == 0);
		{
			return false;
		}
		for (int i = 0; i < states.size() - 1; i++) {
			if (states.at(i).stateName.compare(x) == 0)
			{
				return true;
			}
		}
		return false;

	}
	int getStateLocation(string x) {
		//search through states and return the position of the State x
		
		for (int i = 0; i < states.size() - 1; i++) {
			if (states.at(i).stateName.compare(x) == 0)
			{
				return i;
			}
		}
	
		cout << "Error, could not find state named " + x;
		return -1;
	}

};

void calcStates(FiniteAutomata NFA, FiniteAutomata DFA, State state);
int main()
{
	FiniteAutomata NFA;
	FiniteAutomata DFA;
	State tempState; //temp state to intiaizing variables
	State newState; //temp state for creating new automata
	State currentState; //probably not necessary, but helped me stay organized
	string tempString; //temp string for naming purposes on new automata state
	map<string, string> transitionMap;

	//CONFIGURABLES
	int stateCount = 3;
	int charCount = 2;
	int finalStateCount = 1;

	//EXAMPLE 1 https://www.geeksforgeeks.org/theory-of-computation-conversion-from-nfa-to-dfa/
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
		State newState = State();
		newState.stateName = to_string(i);
		NFA.states.push_back(newState);
		
	}
	NFA.stateCount = NFA.states.size();
	NFA.finalStates.push_back(NFA.states.at(2));

	//state 0 transitions
	tempState = NFA.states.at(0);
	tempState.transition.push_back("a");
	tempState.transition.push_back("a");
	tempState.transition.push_back("b");
	tempState.transitionState.push_back(NFA.states.at(0));
	tempState.transitionState.push_back(NFA.states.at(1));
	tempState.transitionState.push_back(NFA.states.at(0)); //This causes it to be NFA
	NFA.states.at(0) = tempState;

	//state 1 transitions
	tempState = NFA.states.at(1);
	tempState.transition.push_back("b");
	tempState.transitionState.push_back(NFA.states.at(2));
	NFA.states.at(1) = tempState;

	//state 2 transitions
	tempState = NFA.states.at(2);
	//Bitch is empty

	NFA.print();

	//Start at State 0
	//find out that a maps to states 0 and 1
	//find out that b maps to states 0
	tempState = NFA.states.at(0);
	newState = State();
	currentState = State();
	i = 0;
	queue<State> DFAQueue;
	DFAQueue.push(tempState);

	//first stack should only contain state NFA0
	//then while it goes to state DFA 01, it should contain state NFA0, and  NFA1
	//then when it goes to state DFA 02, it should contain NFA0, NFA2
	//important to figure out when to insert into queue (probably when new state found)


	for (int i = 0; i < tempState.transition.size() - 1; i++) {
		if (transitionMap.count(tempState.transition.at(i)) > 0)
		{
			transitionMap.at(tempState.transition.at(i)) = transitionMap.at(tempState.transition.at(i)) + tempState.transitionState.at(i).stateName;
		}
		else
		{
			transitionMap.insert(pair<string, string>(tempState.transition.at(i), tempState.transitionState.at(i).stateName));
		}
	}

	for (pair<string, string> x : transitionMap) {
		if (!DFA.isExistStateName(x.second))
		{
			//adding new state to DFA
			newState = State();
			newState.stateName = x.second;
			DFA.states.push_back(newState);
			calcStates(NFA, DFA, newState);
		}
		//insert transitions and states discovered by map into our current state
		currentState.transition.push_back(x.first);
		State superTemp = DFA.states.at(DFA.getStateLocation(x.second));
		currentState.transitionState.push_back(superTemp);

	}

	//The new state being input into DFA requires NFA location

	//sorts through transitions of state 0, and adds items to the map
	//map would look like
	//[a,01]
	//[b,0]


	//create DFA state 0, a maps to 0, 1 so create new DFA state 01
	//a(01) b(0)

	
	

	
	




	

	//when looking at DFA state 01 transitions, you look at both NFA state 0 and NFA state 1
	//NFA state 0 transition a goes to 01, and NFA state 1 transition a doesn't exist, so DFA a(01)
	//NFA state 0 transition b goes 0, and NFA state 1 transition b goes to 2, so DFA b(02)
	//since NFA state 2 is a final state, DFA state 02 is a final state

	//when looking at DFA state 02 transitions, you look at both NFA state 0 and NFA state 2
	//NFA state 0 transition a goes to 01, and NFA state 2 transition a doesn't exist, so DFA a(01)
	//NFA state 0 trnasition b goes to 0, and NFA state 2 transition b doesn't exist, so DFA b(0)

	//Therefore you have created the DFA
	//
	//0 a(01) b(0)
	//01 a(01) b(02)
	//02 a(01) b(0) --Final
	//







	


    cout << "Hello World!\n";


}

void calcStates(FiniteAutomata NFA, FiniteAutomata DFA, State state) {
	State currentState = State();
	State tempState = State();
	State newState = State();
	queue<State> DFAQueue;
	map<string, string> transitionMap;
	

	for (char x : state.stateName) {
		DFAQueue.push(NFA.states.at(NFA.getStateLocation(to_string(x))));
	}

	while (!DFAQueue.empty())
	{
		tempState = DFAQueue.front();
		DFAQueue.pop();

		for (int i = 0; i < tempState.transition.size() - 1; i++) {
			if (transitionMap.count(tempState.transition.at(i)) > 0)
			{
				transitionMap.at(tempState.transition.at(i)) = transitionMap.at(tempState.transition.at(i)) + tempState.transitionState.at(i).stateName;
			}
			else
			{
				transitionMap.insert(pair<string, string>(tempState.transition.at(i), tempState.transitionState.at(i).stateName));
			}
		}
	}

	for (pair<string, string> x : transitionMap) {
		if (!DFA.isExistStateName(x.second))
		{
			//adding new state to DFA
			newState = State();
			newState.stateName = x.second;
			DFA.states.push_back(newState);
			calcStates(NFA, DFA, newState);
		}
		//insert transitions and states discovered by map into our current state
		currentState.transition.push_back(x.first);
		State superTemp = DFA.states.at(DFA.getStateLocation(x.second));
		currentState.transitionState.push_back(superTemp);

	}

	return;
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
