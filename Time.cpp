



#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds
{



	Time& Time::setToNow()
	{

		this->m_min = sdds::getTime();
		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& out) const
	{
		int Hwidth = 0;
		int Mwidth = 0;

		int x = m_min;
		int HH = x / 60;
		int MM = x - (HH * 60);

		if (HH >= 0 && HH <= 9)//single digit
		{
			Hwidth = 2;
		}
		else if (HH > 9 && HH < 100)//Double digit
		{
			Hwidth = 2;
		}
		else
		{
			Hwidth = 3;
		}


		if (MM >= 0 && MM <= 9)//single digit
		{
			Mwidth = 2;
		}
		else if (MM > 9 && MM < 100)//Double digit
		{
			Mwidth = 2;
		}
		else
		{
			Mwidth = 3;
		}

		out.fill('0');
		out.width(Hwidth);
		out << HH;
		out << ':';
		out.width(Mwidth);
		out << MM;
		out.fill(' ');
		return out;
	}

	std::istream& Time::read(std::istream& in)
	{
		int HH = 0;
		int MM = 0;
		char one = '\0';

		in >> HH >> one >> MM;

		if (cin.good() && HH >= 0 && MM >= 0 && one == ':')
		{
			m_min = (HH * 60) + MM;
		}

		else
		{
			in.setstate(ios::failbit);
		}

		return in;
	}

	Time& Time::operator-=(const Time& D)
	{
		int variable = 24 * 60; //Variable = 1440
		int pow = 0; //pow = how many times Variable will be added.


		if (this->m_min > D.m_min)
		{
			this->m_min = this->m_min - D.m_min;
		}


		else if (this->m_min < D.m_min)
		{
			pow = D.m_min / variable;

			if (pow == 0)
			{
				this->m_min = ((this->m_min + variable) - D.m_min);
			}

			else
			{
				for (int i = 0; i < pow; i++)
				{
					variable = variable + 1440;
				}

				this->m_min = ((this->m_min + variable) - D.m_min);
			}
		}
		return *this;
	}


	Time Time::operator-(const Time& D)const
	{
		Time T;


		int variable = 24 * 60; //Variable = 1440

		int pow = 0; //pow = how many times Variable will be added.

		T.m_min = this->m_min;


		if (T.m_min > D.m_min)
		{
			T.m_min = T.m_min - D.m_min;
		}


		else if (T.m_min < D.m_min)
		{
			pow = D.m_min / variable;

			if (pow == 0)
			{
				T.m_min = ((T.m_min + variable) - D.m_min);
			}

			else
			{
				for (int i = 0; i < pow; i++)
				{
					variable = variable + 1440;
				}

				T.m_min = ((T.m_min + variable) - D.m_min);
			}
		}


		return T;
	}

	Time& Time::operator+=(const Time& D)
	{

		m_min = m_min + D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const
	{
		Time T;
		T.m_min = this->m_min + D.m_min;
		return T;
	}

	Time& Time::operator=(unsigned int val)
	{
		this->m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val)
	{
		this->m_min = this->m_min * val;
		return *this;
	}

	Time Time::operator *(unsigned int val)const
	{
		Time T;
		T.m_min = this->m_min * val;
		return T;
	}

	Time& Time::operator /= (unsigned int val)
	{
		this->m_min = this->m_min / val;
		return *this;
	}

	Time Time::operator /(unsigned int val)const
	{
		Time T;
		T.m_min = this->m_min / val;
		return T;
	}

	Time::operator int()const
	{
		return (int)this->m_min;
	}

	Time::operator unsigned int()const
	{
		return this->m_min;
	}

	std::ostream& operator<<(std::ostream& out, const Time& D)
	{

		D.write(out);

		return out;
	}

	std::istream& operator>>(std::istream& in, Time& D)
	{
		D.read(in);
		return in;
	}
}