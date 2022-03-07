



#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H

#include "Patient.h"
namespace sdds
{
	class TriagePatient : public Patient
	{
		char* m_symptoms = nullptr;

	public:
		TriagePatient();
		char type() const;
		std::ostream& csvWrite(std::ostream& out) const;
		std::istream& csvRead(std::istream& in);

		std::ostream& write(std::ostream& out) const;
		std::istream& read(std::istream& in);
		~TriagePatient();
	};
}
#endif // !SDDS_TRIAGEPATIENT_H



