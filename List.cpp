# NondeterministicFiniteAutomaton
work in progress

#include "List.h"



List::List(const NondeterministicFiniteAutomaton* list, int currNumAutomatons) : m_currNumAutomatons(currNumAutomatons)
{
	setList(list, m_currNumAutomatons);
}


List::List(const List& l)
{
	CopyFrom(l);
}


List& List::operator=(const List& l)
{
	if(this!=&l)
	{
		Destroy();
		CopyFrom(l);
	}
	return *this;
}

void List::CopyFrom(const List& l)
{
	m_currNumAutomatons = l.m_currNumAutomatons;
	setList(l.m_list, m_currNumAutomatons);
}


void List::Destroy()
{
	delete[] m_list;
}

void List::setList(const NondeterministicFiniteAutomaton* list, int currNumAutomatons)
{
	m_list = new NondeterministicFiniteAutomaton[currNumAutomatons];
	for (int i = 0;i<currNumAutomatons;i++)
	{
		m_list[i] = list[i];
	}
}


void List::Open(const char* file)
{
	char* read = new char[10];
	ifstream automatons(file);
	if (automatons.is_open())
	{
		automatons >> read;
		automatons.close();
	}
	int l = strlen(read);
	int numOfAutomatons = 0;
	int dec = 1;
	for (int i = 2;i < l;i++)
	{
		numOfAutomatons = numOfAutomatons*dec + (read[i] - '0');
		dec *= 10;
	}
	m_currNumAutomatons = 1;
	m_list = new NondeterministicFiniteAutomaton[numOfAutomatons];
	for(int i=0;i<numOfAutomatons;i++)
	{
		m_list[i].Read(m_currNumAutomatons++,file);
	}
	m_currNumAutomatons--;
}


void List::Print() const
{
	for(int i=1;i<m_currNumAutomatons+1;i++)
	{
		Print(i);
	}
}

void List::Print(int id) const 
{
	for (int i = 0;i < m_currNumAutomatons;i++)
	{
		if (m_list[i].getId() == id)m_list[i].print();
	}
}
bool List::Empty(int id) const
{
	for (int i = 0;i < m_currNumAutomatons;i++) 
	{
		if (m_list[i].getId() == id)return m_list[i].Empty();
	}
	cout << "There isn't a Nondeterministic Finite Automaton in this list with this ID" << endl;
	return false;
}


bool List::Recognize(int id, const char* word) const
{
	for (int i = 1;i < m_currNumAutomatons + 1;i++) {
		char* positions = new char[2];
		positions[0] = m_list[i].getStartingPoint();
		positions[1] = '\0';
		if (m_list[i].getId() == id) return m_list[i].Recognize(word, word[0], 0, positions);
	}
}

bool List::Deterministic(int id) const
{
	for (int i = 1;i < m_currNumAutomatons + 1;i++) {
		if (m_list[i].getId() == id) return m_list[i].Deterministic();
	}
}
