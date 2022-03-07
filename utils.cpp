

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{


    bool debug = false;
    

    int getTime()
    {
        int mins = -1;
        if (debug) {
            Time t(0);
            cout << "Enter current time: ";
            do {
                cin.clear();
                cin >> t;   
                if (!cin) {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else {
                    mins = int(t);
                }
                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }




    int getInt(const char* prompt)
    {



        int number = 0;
        if (prompt != nullptr)
        {
            cout << prompt;
        }


        bool check = false;


        while (!check)
        {
            cin >> number;

            if ((cin.good()) && (cin.get() != '\n'))
            {
                cout << "Enter only an integer, try again: ";

                cin.clear();
                cin.ignore(100, '\n');
                check = false;
            }

            else if (cin.fail())
            {
                cout << "Bad integer value, try again: ";

                cin.clear();
                cin.ignore(100, '\n');
                check = false;
            }

            else
            {
                check = true;



            }
            cin.clear();

        }


        return number;

    }

    int getInt(int min, int max, const char* prompt, const char* error, bool showRange)
    {
        int valid = 0;
        int loop = 0;
        bool check = false;

        while (!check)
        {
            loop++;
            if (prompt != nullptr)
            {
                if (loop > 1)
                {
                    valid = getInt();

                }
                else//Entered loop first time
                {
                    valid = getInt(prompt);
                }

            }

            
            else
            {
                valid = getInt();

            }


            if (valid >= min && valid <= max)
            {
                check = true;
            }

            else
            {
                check = false;
                if (error != nullptr)
                {
                    cout << error;
                }

                if (showRange)
                {
                    cout << "[" << min << " <= value <= " << max << "]: ";
                }
            }

        }

        return valid;
    }


    char* getcstr(const char* prompt, std::istream& in, char delimiter)
    {
        char* line = nullptr;
        string str;
        int len;
        if (prompt != nullptr)
        {
            cout << prompt;
        }
        getline(in, str);
        len = str.length();

        line = new char[len + 1];
        strcpy(line, str.c_str());
        

        return line;

    }





}