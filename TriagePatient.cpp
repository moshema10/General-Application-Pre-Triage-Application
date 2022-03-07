



#define CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include "TriagePatient.h"


using namespace std;
namespace sdds
{
	int nextTriageTicket = 1;


	TriagePatient::TriagePatient() : Patient(nextTriageTicket)
	{
		m_symptoms = nullptr;
		nextTriageTicket += 1;
	}

	char TriagePatient::type() const
	{
		return 'T';
	}

	std::ostream& TriagePatient::csvWrite(std::ostream& out) const
	{
		Patient::csvWrite(out);
		out << ',' << m_symptoms;
		return out;
	}

	std::istream& TriagePatient::csvRead(std::istream& in)
	{
		string str;

		delete[] m_symptoms;
		Patient::csvRead(in);
		in.ignore();
		getline(in, str, '\n');


		int len = str.length();
		m_symptoms = new char[len + 1];
		strcpy(m_symptoms, str.c_str());
		

		nextTriageTicket = Patient::number() + 1;
		return in;

	}


	std::ostream& TriagePatient::write(std::ostream& out) const
	{
		if (fileIO())
		{
			csvWrite(out);
		}
		else
		{
			out << "TRIAGE" << endl;
			Patient::write(out);
			out << '\n';

			out << "Symptoms: " << m_symptoms << endl;
		}

		return out;
	}

	std::istream& TriagePatient::read(std::istream& in)
	{
		if (fileIO())
		{
			csvRead(in);
		}
		else
		{
			string str;
			delete[] m_symptoms;
			Patient::read(in);
			cout << "Symptoms: ";
			getline(in, str, '\n');
			int len = str.length();
			m_symptoms = new char[len + 1];
			strcpy(m_symptoms, str.c_str());
			
		}

		return in;
	}

	TriagePatient::~TriagePatient()
	{
		delete[] m_symptoms;
	}
}