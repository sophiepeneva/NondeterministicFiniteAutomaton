# NondeterministicFiniteAutomaton
work in progress

#include "NondeterministicFiniteAutomaton.h"


NondeterministicFiniteAutomaton::NondeterministicFiniteAutomaton(int id, const char* paths,
	int numOfPoints, int numOfPaths, int numOfEndingPoints
	, const char* endingPoints, const char startingPoint) :
	m_id(id), m_numOfPoints(numOfPoints), m_numOfPaths(numOfPaths), m_numOfEndingPoints(numOfEndingPoints)
{
	setPaths(paths);
	setEndingPoints(endingPoints);
	setStartingPoint(startingPoint);
}

NondeterministicFiniteAutomaton::NondeterministicFiniteAutomaton(const NondeterministicFiniteAutomaton& NFA)
{
	CopyFrom(NFA);
}

NondeterministicFiniteAutomaton& NondeterministicFiniteAutomaton::operator=(const NondeterministicFiniteAutomaton& NFA)
{
	if(this!=&NFA)
	{
		Destroy();
		CopyFrom(NFA);
	}
	return *this;
}

void NondeterministicFiniteAutomaton::Destroy()
{
	delete[] m_paths;
	delete[] m_endingPoints;
}

void NondeterministicFiniteAutomaton::setPaths(const char* paths)
{
	m_paths = new char[strlen(paths) + 1];
	strcpy_s(m_paths, strlen(paths) + 1, paths);
}

void NondeterministicFiniteAutomaton::setEndingPoints(const char* endingPoints)
{
	m_endingPoints = new char[strlen(endingPoints) + 1];
	strcpy_s(m_endingPoints, strlen(endingPoints) + 1, endingPoints);
}

void NondeterministicFiniteAutomaton::CopyFrom(const NondeterministicFiniteAutomaton& NFA)
{
	m_id = NFA.m_id;
	m_numOfPaths = NFA.m_numOfPaths;
	m_numOfEndingPoints = NFA.m_numOfEndingPoints;
	m_numOfPoints = NFA.m_numOfPoints;
	setPaths(NFA.m_paths);
	setStartingPoint(NFA.m_startingPoint);
	setEndingPoints(NFA.m_endingPoints);
}


void NondeterministicFiniteAutomaton::Read(int numOfAutomatons, const char* file)
{
	ifstream automatons(file);
	char read[200];
	bool automatonNotFound = true;
	if (automatons.is_open())
	{
		while (automatonNotFound==true)
		{
			automatons >> read;
			if (read[0] == 'A' && read[1]!='=')
			{
				int l = strlen(read);
				int dec = 1;
				int currFoundAutomatonNum = 0;
				for(int i=1;i<l;i++)
				{
					if ((read[i] - '0') >= 0 && (read[i] - '0') <= 9) {
						currFoundAutomatonNum = currFoundAutomatonNum * dec + (read[i]-'0');
						dec *= 10;
					}
					else { i = l; }
				}
				
				if (currFoundAutomatonNum == numOfAutomatons)
				{
					automatonNotFound = false;
					automatons >> read;
				}
			}
		}
		automatons.close();
		setPaths(read);
		m_id = numOfAutomatons;
		DevideIntoMembers();
	}
}

void NondeterministicFiniteAutomaton::DevideIntoMembers()
{
	int dec = 1;
	int i = 0;
	while (m_paths[i] != ',')
	{
		m_numOfPoints = m_numOfPoints * dec + (m_paths[i] - '0');
		dec *= 10;
		i++;
	}
	dec = 1;
	i++;
	while (m_paths[i] != ',')
	{
		m_numOfPaths = m_numOfPaths * dec + (m_paths[i] - '0');
		dec *= 10;
		i++;
	}
	m_startingPoint = m_paths[++i];
	i += 2;
	dec = 1;
	while (m_paths[i] != ':')
	{
		m_numOfEndingPoints = m_numOfEndingPoints * dec + (m_paths[i] - '0');
		dec *= 10;
		i++;
	}
	i += 2;
	int counter = 0;
	m_endingPoints = new char[m_numOfPoints*m_numOfEndingPoints];
	while (m_paths[i] != ')')
	{
		m_endingPoints[counter++] = m_paths[i];
		i++;
	}
	m_endingPoints[counter] = '\0';
}

void NondeterministicFiniteAutomaton::print() const 
{
	cout << "Starting point : " << m_startingPoint << endl
		<< "Ending points : " << m_endingPoints << endl;
	int l = strlen(m_paths);
	bool startDrawing = false;
	for(int i=0;i<l;i++)
	{
		if (m_paths[i] == ';')startDrawing = true;
		if(startDrawing==true)
		{
			i++;
			while(m_paths[i]=='(')
			{
				i++;
				while (m_paths[i] != ',') 
				{
					if ((m_paths[i] - '0') >= 0 && (m_paths[i] - '0') <= 9)
					{
						cout << m_paths[i] - '0';
					}
					else { cout << m_paths[i]; }
					i++;
				}
				if(m_paths[i]==',')
				{
					cout << "-";
					i++;
					while (m_paths[i] != ',')
					{
						if ((m_paths[i] - '0') >= 0 && (m_paths[i] - '0') <= 9)
						{
							cout << m_paths[i] - '0';
						}
						else { cout << m_paths[i]; }
						i++;
					}
					cout << "->";
				}
				if (m_paths[i] == ',') {
					i++;
					while (m_paths[i] != ')')
					{
						if ((m_paths[i] - '0') >= 0 && (m_paths[i] - '0') <= 9)
						{
							cout << m_paths[i] - '0';
						}
						else { cout << m_paths[i]; }
						i++;
					}
					i++;
					cout << endl;
				}
			}
		}
	}
}

bool NondeterministicFiniteAutomaton::isPointEnding(char point) const
{
	int l = strlen(m_endingPoints);
	for(int i=0;i<l;i++)
	{
		if (point == m_endingPoints[i])return true;
	}
	return false;
}


bool NondeterministicFiniteAutomaton::Recognize(const char* word, char letter, int letterIndex, const char* positions) const
{
	if (Empty())return false;
	int lWord = strlen(word);
	int lPos = strlen(positions);
	if (letterIndex == lWord)
	{
		for(int i=0;i<lPos;i++)
		{
			if(positions[i]!=',')
			{
				if (isPointEnding(positions[i]))return true;
			}
		}
	}
	char* newPositions = new char[m_numOfPoints * 2];
	int posCounter = 0;
	int l = strlen(m_paths);
	bool startCheking = false;
	bool foundAtleastOnePath = false;
	for(int j=0;j<lPos;j++)
	{
			for (int i = 0;i < l;i++)
			{
				if (m_paths[i] == ';')startCheking = true;
				if (startCheking == true) {
					if (m_paths[i] == positions[j] && m_paths[i] != ','&&m_paths[i - 1]  == '(')
					{
						i += 2;
						if (letterIndex != lWord) {
							if (m_paths[i] == letter || m_paths[i] == 'ε')
							{
								foundAtleastOnePath = true;
								newPositions[posCounter++] = m_paths[i + 2];
								newPositions[posCounter++] = ',';
								i += 3;
							}
						}
						else
						{
							if (m_paths[i] == 'ε')
							{
								foundAtleastOnePath = true;
								newPositions[posCounter++] = m_paths[i + 2];
								newPositions[posCounter++] = ',';
								i += 3;
							}
						}
					}
				}
			}
	}
	newPositions[--posCounter] = '\0';
	if (foundAtleastOnePath == false)return false;
	return Recognize(word, word[++letterIndex], letterIndex, newPositions);
}



bool NondeterministicFiniteAutomaton::Deterministic() const
{
	char* currPosition = new char[5];
	int l = strlen(m_paths);
	bool startChecking = false;
	for(int i=0;i<l;i++)
	{
		if (m_paths[i] == ';')startChecking = true;
		if(startChecking==true)
		{
			
		}
	}
}
