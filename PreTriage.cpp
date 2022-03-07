



#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>

#include <cstring>
#include "PreTriage.h"
#include "utils.h"
#include "Patient.h"
#include "CovidPatient.h"
#include "TriagePatient.h"

using namespace std;
namespace sdds
{
	PreTriage::PreTriage(const char* dataFilename) : m_averCovidWait(15), m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		if (dataFilename != nullptr)
		{
			delete[] m_dataFilename;
			int len = strlen(dataFilename);
			m_dataFilename = new char[len + 1];
			strcpy(m_dataFilename, dataFilename);
			m_dataFilename[len] = '\0';
		}
		load();
		
	}

	PreTriage::~PreTriage()
	{
		ofstream out;
		out.open(m_dataFilename);
		if (out.is_open())
		{
			out << m_averCovidWait;
			out << ',';
			out << m_averTriageWait;
			out << '\n';

			for (int i = 0; i < m_lineupSize; i++)
			{
				m_lineup[i]->fileIO(true);
				out << *m_lineup[i] << '\n';
			}
			out.close();
			out.clear();
		}
		
		

		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		cout << "Saving m_lineup..." << endl;
		for (int i = 0; i < m_lineupSize; i++)
		{
			cout << i+1 << "- ";
			m_lineup[i]->fileIO(true);
			cout << *m_lineup[i];
			cout << '\n';
		}
		for (int i = 0; i < m_lineupSize; i++)
		{
			delete m_lineup[i];
		}
		
		delete[] m_dataFilename;
		cout << "done!" << endl;

	}

	const Time PreTriage::getWaitTime(const Patient& p)const
	{
		int count = 0;
		char one_char = '\0';
		one_char = p.type();

		for (int i = 0; i < m_lineupSize; i++)
		{
			if (m_lineup[i] == &p)
			{
				count++;
			}
		}

		if (one_char == 'C')
		{
			if (count==1)
			{
				return 0;
			}
			else
			{
				return count * (int)m_averCovidWait;
			}
			
			
		}
		if (one_char == 'T')
		{
			if (count == 1)
			{
				return 0;
			}
			else
			{
				return count * (int)m_averTriageWait;
			}
			
		}
		return 0;
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		sdds::debug = true;
		int CT = getTime();
		int PTT = Time(p);
		int AWT = 0;
		if (p.type() == 'C')
		{
			AWT = (int)m_averCovidWait;
		}
		else
		{
			AWT = (int)m_averTriageWait;
		}
		int PTN = p.number();

		
		AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;

		if (p.type() == 'C')
		{
			m_averCovidWait = AWT;
		}
		else
		{
			m_averTriageWait = AWT;
		}
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement<Patient>(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{
		for (int i = 0; i < m_lineupSize; i++)
		{
			if (*m_lineup[i] == type)
			{
				return i;
			}
		}
		return -1;
	}

	void PreTriage::load()
	{
		cout << "Loading data..." << endl;

		ifstream in;
		in.open(m_dataFilename);
		if (in.is_open())
		{
			
			in >> m_averCovidWait;
			in.ignore(100,',');
			in >> m_averTriageWait;
			in.ignore(100,'\n');

			Patient* P = nullptr;
			int count = 0;
			int no = 0;
			for (int i = 0; i < maxNoOfPatients && in.good(); i++)
			{
				count++;
				bool flag = false;

				char one_char = 'w';
				in >> one_char;
				in.ignore();

				if (one_char == 'C')
				{
					P = new CovidPatient;
					flag = true;
				}
				if (one_char == 'T')
				{
					P = new TriagePatient;
					flag = true;
				}

				if (flag)
				{
					P->fileIO(true);
					in >> *P;
					P->fileIO(false);
					m_lineup[i] = P;
					
					m_lineupSize++;
				}
			}
			string str;
			while (getline(in,str))
			{
				no++;
			}

			if (no != 0)
			{
				cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
			}

			if (count == 0)
			{
				cout << "No data or bad data file!" << endl << endl;;
			}
			else if (count < 100)
			{
				cout << count - 1 << " Records imported..." << endl << endl;;
			}
			else
			{
				cout << count << " Records imported..." << endl << endl;
			}
			
			in.close();
			in.clear();
		}
		else
		{
			cout << "No data or bad data file!" << endl;
		}
		
	}

	void PreTriage::reg()
	{
		if (m_lineupSize == maxNoOfPatients)
		{
			cout << "Line up full!" << endl;
			return;
		}


		int selection = 0;

		int index = m_lineupSize;
		m_pMenu >> selection;
		if (selection==1)
		{
			m_lineup[index] = new CovidPatient;
			m_lineupSize++;
		}
		else if (selection == 2)
		{
			m_lineup[index] = new TriagePatient;
			m_lineupSize++;
		}
		else
		{
			return;
		}
		sdds::debug = true;
		m_lineup[index]->setArrivalTime();
		cout << "Please enter patient information: " << endl;
		m_lineup[index]->fileIO(false);
		cin >> *m_lineup[index];
		cout << '\n';
		for (int i = 0; i < 42; i++)
		{
			cout << '*';
		}
		cout << '\n';
		cout << *m_lineup[index];
		
		cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[index]) << endl;
		for (int i = 0; i < 42; i++)
		{
			cout << '*';
		}
		cout << '\n' << endl;
	}


	void PreTriage::admit()
	{
		int selection = 0;
		char type = '\0';
		m_pMenu >> selection;
		if (selection==1)
		{
			type = 'C';
		}
		else if (selection==2)
		{
			type = 'T';
		}
		else
		{
			return;
		}
		int index = indexOfFirstInLine(type);
		if (index == -1)
		{
			return;
		}
		cout << '\n';
		for (int i = 0; i < 42; i++)
		{
			cout << '*';
		}
		cout << '\n';
		m_lineup[index]->fileIO(false);
		cout << "Calling for ";
		cout << *m_lineup[index];
		for (int i = 0; i < 42; i++)
		{
			cout << '*';
		}
		cout << '\n' << endl;

		setAverageWaitTime(*m_lineup[index]);
		removePatientFromLineup(index);
	}

	void PreTriage::run(void)
	{
		int selection = 0;
		bool flag = false;

		do
		{
			m_appMenu >> selection;
			if (selection==0)
			{
				flag = false;
				return;
			}
			else
			{
				if (selection==1)
				{
					reg();
				}
				else
				{
					admit();
				}
				flag = true;
			}


		} while (flag);
	}
}