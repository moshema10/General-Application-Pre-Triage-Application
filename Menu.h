




#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds
{
    class Menu
    {
        char* m_text = nullptr; 
        int m_noOfSel = -1;  
        void display()const;
    public:

        Menu();
        Menu(const char* MenuContent, int NoOfSelections);

        
        Menu(const Menu& other);
        Menu& operator=(const Menu& other) = delete; 

        virtual ~Menu();


        int& operator>>(int& Selection);


    };
}


#endif // !SDDS_MENU_H

