# NondeterministicFiniteAutomaton
work in progress

#pragma once
#include "NondeterministicFiniteAutomaton.h"
#include<string>
using namespace std;

class List
{
public:
	List(const NondeterministicFiniteAutomaton* list = new NondeterministicFiniteAutomaton(), int currNumAutomatons = 0);
	List(const List& l);
	List& operator=(const List& l);
	~List() { Destroy(); }

	void Open(const char* file);
	void Print() const;
	void Print(int id) const;
	void setList(const NondeterministicFiniteAutomaton* list, int currNumAutomatons);

	bool Deterministic(int id) const;
	bool Recognize(int id, const char* word) const;
	bool Empty(int id) const;

	NondeterministicFiniteAutomaton& Union(int id);
	NondeterministicFiniteAutomaton& Concat(int id);
	NondeterministicFiniteAutomaton& Un(int id);

private:
	void Destroy();
	void CopyFrom(const List& l);
	NondeterministicFiniteAutomaton * m_list;
	int m_currNumAutomatons;
};


