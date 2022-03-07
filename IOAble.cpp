



#include <iostream>
#include "IOAble.h"

using namespace std;
namespace sdds
{


	IOAble::~IOAble()
	{

	}

	std::ostream& operator<<(std::ostream& out, const IOAble& A)
	{
		A.write(out);
		return out;

	}

	std::istream& operator>>(std::istream& in, IOAble& B)
	{
		B.read(in);
		return in;
	}
}