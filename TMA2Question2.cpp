//: TMA2Question2

/*
 Title: TMA2Question2.cpp
 Description: Dynamic storage allocation example
 Date: Feb 4, 2013
 Author: Danny J. Cortez 2997314
 Version: 1.0
*/

/*
 DOCUMENTATION

 Program Purpose:
 	Dynamic storage allocation example.

 Compile (assuming Cygwin is running): g++ -o TMA2_2 TMA2Question2.cpp
 Execution (assuming Cygwin is running): ./TMA2_2.exe

 Classes: none

 Variables:
    int  - arraySize: the size of the arrays
    int - i: int pointer to dynamically allocated int var
    long - l: int pointer to dynamically allocated int var
    char -  c: char pointer to dynamically allocated char array
    float - f: float pointer to dynamically allocated float array

*/

/*
 TEST PLAN

 Normal case: The only case. Allocate storage and fill them; then delete them.

 Discussion:
 	A program that dynamically creates pieces of storage of the following types using
 	new: int, long, an array of 100 chars, and an array of 100 floats. Prints the addresses
 	and values of these using the format: “type @ <address>= <value>”. After the addresses and
 	values have been printed, frees the storage using delete. Fills the char array using
 	copies of the lowercase and uppercase alphabet (a-z, A-Z), and fills the float array using
 	sequential numbers starting with 101.

*/

#include <iostream>
#include <cstring>
#include <cstddef>

using namespace std;

int main ()
{
    int arraySize = 100;

    int* i = new int;
    long* l = new long;
    char* c = new char[arraySize];
    float* f = new float[arraySize];

    /**** Float ****/
    //Initialize all to 0;
    for (int i = 0; i < 100; i ++)
    {
        f[i] = 0;
    }


    for (int j = 0; j < 100; j++)
    {

        f[j]= (float)(j+101);
        cout << "Float @ " << (long)&f[j] << " = " << f[j] << endl;
    }

    delete[]f;
    f = 0;
    cout << "Deleted float" << endl;

   /**** Int ****/

    *i = -999;
    cout << "Int @ " << (long)&i << " = " << *i << endl;
    delete i;
    i = 0;
    cout << "Deleted int" << endl;

    /**** Long ****/

    *l = 999999999;
    cout << "Long @ " << (long)&l << " = " << *l << endl;
    delete l;
    l = 0;
    cout << "Deleted long" << endl;


    /**** Char ****/
    //for (int i = 0; i < 100; i ++)
    //{
      //  c[i] = '*';
    //}
    c[0] = {'*'};


    for (int j = 0; j < 25; j++)
    {

        c[j] = j + 97; //97 = 'a'; start this @ element 0

    }

    for (int k = 25; k < 51; k++)
    {
        c[k] = k + 40;// 65 = 'A'; start this @ element 25

    }
    for (int l = 0; l < 100; l++)
    {
        cout << "Char @ " << (long)&c[l] << " = " << c[l] << endl;
    }


    delete []c;
    c = 0;
    cout << "Deleted char" << endl;

}
