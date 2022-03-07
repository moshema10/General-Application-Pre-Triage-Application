





#ifndef SDDS_PATIENT_H
#define SDDS_PATIENT_H


#include "IOAble.h"
#include "Ticket.h"
#include "Time.h"
namespace sdds
{
	class Patient : public IOAble
	{
		char* m_patientName = nullptr;
		int m_OHIP = 0;
		Ticket m_ticket;

		
		bool m_IOflag = false;

	public:
		Patient(int number = 0, bool flag = false);
		Patient(const Patient& other) = delete;
		Patient& operator=(const Patient& other) = delete;
		~Patient();


		
		virtual char type() const = 0;
		bool fileIO() const;
		void fileIO(bool flag);
		bool operator==(const char single) const;
		bool operator==(const Patient& other) const;

		void setArrivalTime();
		operator Time() const;
		int number() const;


		std::ostream& csvWrite(std::ostream& out) const;
		std::istream& csvRead(std::istream& in);

		
		std::ostream& write(std::ostream& out) const;
		std::istream& read(std::istream& in);



	};
}

#endif // !SDDS_PATIENT_H

