# NondeterministicFiniteAutomaton
work in progress

#pragma once
#include<iostream>
#include <fstream>

using namespace std;


class NondeterministicFiniteAutomaton
{
public:
	NondeterministicFiniteAutomaton(int id=0, const char* paths="", int numOfPoints = 0, int numOfPaths = 0, int numOfEndingPoints = 0, const char* endingPoint="", const char startingPoint = '0');
	NondeterministicFiniteAutomaton(const NondeterministicFiniteAutomaton& NFA);
	NondeterministicFiniteAutomaton& operator=(const NondeterministicFiniteAutomaton& NFA);
	~NondeterministicFiniteAutomaton() { Destroy(); }

	void setPaths(const char* paths);
	void setEndingPoints(const char* endingPoints);
	void setStartingPoint(const char startingPoint) { m_startingPoint = startingPoint; }
	void setId(int id) { m_id = id; }
	void setNumOfPoints(int numOfPoints) { m_numOfPoints = numOfPoints; }
	void setNumOfPaths(int numOfPaths) { m_numOfPaths = numOfPaths; }
	void setNumOfEndingPoints(int numOfEndingPoints) { m_numOfEndingPoints = numOfEndingPoints; }

	int getId() const { return m_id; }
	char* getPaths() const { return m_paths; }
	char getStartingPoint() const { return m_startingPoint; }
	char* getEndingPoints() const { return m_endingPoints; }
	int getNumOfEndingPoints() const { return m_numOfEndingPoints; }
	int getNumOfPaths() const { return m_numOfPaths; }
	int getNumOfPoints() const { return m_numOfPoints; }

	void DevideIntoMembers();
	void Read(int numOfAutomatons, const char* file);
	void print()const;
	bool isPointEnding(char point) const;
	bool Empty() const { return m_numOfEndingPoints == 0; }
	bool Recognize(const char* word , char letter, int letterIndex, const char* positions) const;
	bool Deterministic() const;

private:
	void Destroy();
	void  CopyFrom(const NondeterministicFiniteAutomaton& NFA);
	char* m_endingPoints;
	char m_startingPoint;
	int m_numOfPoints;
	int m_numOfPaths;
	int m_numOfEndingPoints;
	int m_id;
	char* m_paths;
};

