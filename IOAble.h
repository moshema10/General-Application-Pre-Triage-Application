
#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream>


namespace sdds
{
	class IOAble
	{
	public:
		virtual std::ostream& csvWrite(std::ostream& out) const = 0;
		virtual std::istream& csvRead(std::istream& in) = 0;

		virtual std::ostream& write(std::ostream& out) const = 0;
		virtual std::istream& read(std::istream& in) = 0;

		virtual ~IOAble();
	};
	std::ostream& operator<<(std::ostream& out, const IOAble& A);
	std::istream& operator>>(std::istream& in, IOAble& B);
}
#endif // !SDDS_IOABLE_H


