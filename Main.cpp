# NondeterministicFiniteAutomaton
work in progress

#include<iostream>
#include "List.h"

using namespace std;

int main()
{
	List l1;
	l1.Open("automatons.txt");
	char* word = new char[9];
	strcpy_s(word, 9, "aaabcddd");
	if (l1.Recognize(2, word))cout << "This automaton recognizes the word " << word << endl;
	else
	{
		cout << "This automaton does not recognize the word " << word << endl;
	}
	system("pause");
}
