





#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include "Patient.h"
#include "utils.h"

using namespace std;
namespace sdds
{

	Patient::Patient(int number, bool flag) : m_ticket(number)
	{
		m_IOflag = flag;
	}
	Patient::~Patient()
	{
		delete[] m_patientName;
	}

	bool Patient::fileIO() const
	{
		return m_IOflag;
	}

	void Patient::fileIO(bool flag)
	{
		m_IOflag = flag;
	}

	bool Patient::operator==(const char single) const
	{
		if (this->type() == single)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Patient::operator==(const Patient& other) const
	{
		if (this->type() == other.type())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Patient::setArrivalTime()
	{
		this->m_ticket.resetTime();

	}

	Patient::operator Time() const
	{
		return (Time)m_ticket;
	}

	int Patient::number() const
	{
		return m_ticket.number();
	}

	std::ostream& Patient::csvWrite(std::ostream& out) const
	{
		out << type() << "," << m_patientName << "," << m_OHIP << ",";
		m_ticket.csvWrite(out);

		return out;
	}

	std::istream& Patient::csvRead(std::istream& in)
	{
		string str;
		getline(in, str, ',');


		int len = str.length();
		delete[] m_patientName;
		m_patientName = new char[len + 1];
		strcpy(m_patientName, str.c_str());
		

		in >> m_OHIP;
		in.ignore();

		m_ticket.csvRead(in);

		return in;
	}

	std::ostream& Patient::write(std::ostream& out) const
	{
		m_ticket.write(out);
		out << '\n';

		int len = strlen(m_patientName);
		if (len > 25)
		{
			for (int i = 0; i < 25; i++)
			{
				out << m_patientName[i];
			}
		}
		else
		{
			out << m_patientName;
		}

		out << ", OHIP: " << m_OHIP;

		return out;
	}

	std::istream& Patient::read(std::istream& in)
	{
		string str;
		cout << "Name: ";


		getline(in, str, '\n');
		int len = str.length();

		delete[] m_patientName;
		m_patientName = new char[len + 1];
		strcpy(m_patientName, str.c_str());
		


		cout << "OHIP: ";
		m_OHIP = getInt(100000000, 999999999, nullptr, "Invalid OHIP Number, ");

		return in;
	}

}