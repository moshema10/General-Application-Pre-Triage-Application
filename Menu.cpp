



#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Menu.h"
#include "utils.h"

using namespace std;
namespace sdds
{

	Menu::Menu()
	{
		m_text = nullptr;
		m_noOfSel = -1;
	}

	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		if (MenuContent != nullptr && MenuContent[0] != '\0')
		{
			int len = strlen(MenuContent) + 1;
			delete[] m_text;
			m_text = new char[len];
			strcpy(m_text, MenuContent);

			m_noOfSel = NoOfSelections;
		}
	}

	Menu::~Menu()
	{
		delete[] m_text;

	}

	Menu::Menu(const Menu& other)
	{
		this->m_noOfSel = other.m_noOfSel;
		if (other.m_text != nullptr)
		{
			int len = strlen(other.m_text);

			m_text = new char[len + 1];

			for (int i = 0; i < len; i++)
			{
				m_text[i] = other.m_text[i];
			}
			m_text[len] = '\0';

		}
		else
		{
			m_text = nullptr;
		}
	}

	void Menu::display()const
	{
		cout << m_text << endl;
		cout << "0- Exit" << endl;

	}

	int& Menu::operator>>(int& Selection)
	{
		display();
		int value = getInt(0, m_noOfSel, "> ", "Invalid option ");
		Selection = value;
		return Selection;
	}
}