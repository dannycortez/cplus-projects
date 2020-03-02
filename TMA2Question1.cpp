

/*
 
*/

/*
 DOCUMENTATION

 Program Purpose:
 	A program that manages DVD rental in a “video” rental store.

 Compile (assuming Cygwin is running): g++ -o TMA2_1 TMA2Question1.cpp
 Execution (assuming Cygwin is running): ./TMA2_1.exe

 Classes: none

 Variables:
    string - title: TITLE OF THE DVD
    float - cost: COST OF THE DVD
    string - genre: WHAT TYPE OF DVD
    int - numberOfStock: HOW MANY ARE IN STOCK
    int - count: KEEPS TRACK OF HOW MANY LINES FOR THE TXT FILE IT HAS PROCCESSED
    char - fileName: A CHAR ARRAY THAT CONTAINS THE FILE NAME TO BE OPENED
    string - line: THE LINE FROM THE TEXT FILE OPENED
    int - counter: KEEPS TRACK OF THE TOKENS OF THE LINE
    char - cptr: A POINTER TO THE TOKENS
    char - cstr: A POINTER TO A COPY OF THE LINE
    Video - list: DYNAMICALLY ALLOCATED DVD DATA TYPE
*/

/*
 TEST PLAN

 Normal case:
    Use List.txt; a file w/ ten lines; program will create an array
    of 10 DVD instances.
 Bad case #1:
    Use listssss.xtx; no file exists and program will catch the error.
    Program will exit.
 Bad case #2
    Use List2.txt; a file w/ more than 10 lines. The program will only process
    10 lines.

 Discussion:
 	A program that manages DVD rental in a “video” rental store. Has an abstract
 	data type that represents a DVD in this store. Has all the data and operations
 	that may be necessary for the DVD type to work well within a rental management system.
 	Includes a print() member function that displays all the information about the DVD.

*/
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct Video {

    string title;
    float cost;
    string genre;
    int numberOfStock;


        void print();
        float getCost();
        string getGenre();
        int getNumberInStock();
};

void Video::print()
{
    cout << title << " ";
    cout << cost << " ";
    cout << genre << " ";
    cout << numberOfStock << endl;

}

float Video::getCost()
{
    return cost;
}

string Video::getGenre()
{

    return genre;

}

int Video::getNumberInStock()
{

    return numberOfStock;

}

void proccessString(string, Video*);
void processFile(Video*);
void creatDVDs(Video*);

/****************************************/
void processFile(Video* list)
{

    int count = 0;
    char fileName[100];
    string line;

    cout << "Enter file name..." << endl;
    cin >> fileName;

    ifstream in(fileName);

    if (in.is_open())
    {
        cout << "Opened file..." << endl;
        while (getline(in,line) && count < 10)
        {
            count++;
            proccessString(line,list);
            list++;
        }
    }
    else
    {
        cout << "Error opening file...try again" << endl;
        exit (EXIT_FAILURE);
    }


}

/****************************************/

void proccessString(string currentLine, Video* list)
{
    int counter = 0;
    char *cptr =0;
    char *cstr = new char[currentLine.length()+1];

    strcpy (cstr, currentLine.c_str());
    cptr = strtok (cstr,"$~");
    list->title = cptr;//First token will be title

    while (cptr != 0)
    {
        cptr = strtok (NULL, "$~");
        if (cptr != NULL)
        {

            counter++;
            if (counter == 1)//Second token will be cost
            {
               list->cost = atof(cptr);
            }
            if (counter == 2)//3rd token will be genre
            {
                list->genre = cptr;
            }
            if (counter == 3)//4th token will be qty
            {
                list->numberOfStock = atoi(cptr);
            }
        }
    }
    delete []cstr;

}
/****************************************/
void creatDVDs(Video* list)
{

    processFile(list);

}
/****************************************/

int main()
{
    int listSize = 10;

    Video* list = new Video[listSize];


    creatDVDs(list);
    int count = 0;

    for (int i = 0; i < listSize; i++)
    {

        list[i].print();

    }

    delete []list;
    list = 0;
}
