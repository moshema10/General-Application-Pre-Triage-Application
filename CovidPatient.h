



#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_

#include "Patient.h"
namespace sdds
{
	class CovidPatient : public Patient
	{
	public:
		CovidPatient();
		char type() const;
		std::istream& csvRead(std::istream& in);
		std::ostream& write(std::ostream& out) const;
		std::istream& read(std::istream& in);
	};
}
#endif // !SDDS_COVIDPATIENT_H_




