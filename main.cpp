#include "structlist.h"
#include "datafunction.h"
#include "loginfunction.h"
#include "displayfunction.h"

using namespace std;

int main()
{
    string YearFile = "Listyear";
    Schoolyear* DataBase = nullptr;
    LoadData(YearFile, DataBase);
    
    int key = login(DataBase);
    if (key == 1)
        StudentGUI(DataBase);
    if (key == 2)
        StaffGUI(DataBase);
    
    SaveData(YearFile,DataBase);
    ClearData(DataBase);
}