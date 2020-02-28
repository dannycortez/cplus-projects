/*
 Title: ExtSorting.cpp
 Description: Simulates General Multiway External Mergesort
 Version: 1.0
*/

/*
 DOCUMENTATION

 Program Purpose:
 	Simulates General Multiway External Mergesort

 Compile: using Microsoft Visual Studio
 Normal: using Microsoft Visual Studio
 Debug:  using Microsoft Visual Studio

 Execution using Microsoft Visual Studio

 Classes: none

 */

/*
 TEST PLAN

 Normal case:
 
 Bad Data case 1 

 Bad Data case 2 

 Discussion:
 	This program attemps to: take  four command-line input parameters:
	(i) page size, (ii) the number of buffer pages, (iii) the name of an input file containing
	all data to be inserted, and (iv) the name of an output file. For example 
	Comp4380.cs.umanitoba.ca<2> ExtSorting 2 3 SIDs.txt SortedSIDs.txt 

*/



#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm> 

using namespace std;

int pageSize;
int records;
float numPages;

vector<int> unSortedValues;
vector<int> lastRun;
vector<vector<int>> runs;
vector<vector<int>> tempRuns;

void proccessString(string currentLine);
void mergeSort(vector<int> temp, int b);
void sort2(vector<int> unsortedVector);
void printRead(vector<int> read);
//*************************************
//prints a list of the current "subfile"
void printRead(vector<int> read)
{
	printf("[");
	for(size_t j=0; j < read.size(); j++)
	{
  		printf("%i ", read[j]);
	}
	printf("]");
}

//*************************************
// simulates the merge sort algorithm
void mergeSort(vector<int> temp, int b)
{
	vector<int> temp1;
	vector<int> temp2;
	vector<int> s1;
	vector<int> s2;
	
	
	size_t tempsize = temp1.size();
	int s = (int)tempsize;
	int reset = 0;
	int pass = 0;
	int count = 0;
	size_t length;
	
	//pass 0
	printf("Pass %i\n", pass);
	printf("Read [");
	for(size_t i=0; i < temp.size(); i++)
		{
  			printf(" %i", temp[i]);

			temp1.push_back(temp[i]);

			s = (int)temp1.size();
			//records fit in page size
			if (s == (b * pageSize))
			{
				printf("]\n");
				printf("Write [");
				sort (temp1.begin(), temp1.end()); 
				auto last = unique (temp1.begin(), temp1.end());// duplicate elimination
				temp1.erase(last, temp1.end()); // duplicate elimination
				runs.push_back(temp1);
				for(size_t j=0; j < temp1.size(); j++)
				{
  					printf(" %i", temp1[j]);
				}
				printf("]\n");
				temp1.clear();
				printf("Read [");
			}
		}
		printf("]\n");
		//records less than page size
		if (temp1.size() > 0)
		{
			sort (temp1.begin(), temp1.end()); 
			auto last = unique (temp1.begin(), temp1.end());// duplicate elimination
			temp1.erase(last, temp1.end());// duplicate elimination
			runs.push_back(temp1);
			printf("Write [");
			for(size_t j=0; j < temp1.size(); j++)
			{
  				printf(" %i", temp1[j]);
			}
			printf("]\n\n");
		}
		pass++;		
		//passes 1 and up
		while (runs.size() > 0)
		{
			tempRuns.clear();
			printf("Pass %i\n", pass);
			printf("Read ");
			length = runs.size();
			for (size_t j=0; j < length; j++)
			{
				
				if(runs.size() == 0)
				{
					tempRuns.clear();
					break;
				}

				if((int)runs.size() >=pageSize)
				{
					s1 = runs[0];
					s2 = runs[1];
					printRead(s1);
					printf(" ");
					printRead(s2);  
					printf("\n");
					for(size_t k=0; k < s2.size(); k++)
					{
  						s1.push_back(s2[k]);
					}
					sort (s1.begin(), s1.end());
					auto last = unique (s1.begin(), s1.end());// duplicate elimination
					s1.erase(last, s1.end());// duplicate elimination
					printf("Write ");
					printRead(s1);
					tempRuns.push_back(s1);
					lastRun = s1;
					runs.erase(runs.begin(),runs.begin()+2);
					printf("\n");
				
				}
				else// just one page left
				{
					s1 = runs[0];
					printf("Read ");
					printRead(s1);
					printf("\n");
					sort (s1.begin(), s1.end());
					auto last = unique (s1.begin(), s1.end());// duplicate elimination
					s1.erase(last, s1.end());// duplicate elimination
					printf("Write ");
					printRead(s1);
					printf("\n");
					tempRuns.push_back(s1);
					lastRun = tempRuns[0];
					runs.erase(runs.begin(),runs.begin()+1);
					break;
				}
		
		}
		pass++;
		runs.clear();
		runs = tempRuns;
		printf("\n");
		}
	}
//***********************************
//initial processing of the input file;
//reads file line by line; passes each line to 
//processString method. also counts the number of
//records
int processFile(int pageSize, char* nameOfFile)
{
	records = 0;
    string line;
 	ifstream in(nameOfFile);

    if (in.is_open())
    {
        while (getline(in,line))
        {
            records++;
            proccessString(line);
         }
    }
    else
    {
        cout << "Error opening file...try again" << endl;
        return 0;
    }
	numPages = ceil((float)records/(float)pageSize);

    return 1;
}
//***********************************
// processes the current line read from the
// input file; adds value to initial vector of
// unsorted values
void proccessString(string currentLine)
{
    int counter = 0;
	int value = 0;
    char *cptr =0;
    char *cstr = new char[currentLine.length()+1];
	char *input[2];

    strcpy (cstr, currentLine.c_str());
    cptr = strtok (cstr," ");
	
	input[counter] = cptr;
	value = atoi(cptr);
	unSortedValues.push_back(value);
	
    while (cptr != 0)
    {
        cptr = strtok (NULL, " ");
        if (cptr != NULL)
        {
            input[counter] = cptr;
			value = atoi(cptr);
			counter++;
        }
    }
	
   delete []cstr;
 }
//***********************************
//main method
int main(int argc,char* argv[])
{
    processFile(atoi(argv[2]), argv[4]);
	pageSize = atoi(argv[2]);
	printf("With page size=%i records per page, N=%i records in the %s can fit into P=%i pages. These records are sorted using a general multiway mergesort with B=%i buffer pages.\n", pageSize,records,argv[4],(int)numPages, atoi(argv[3]));
	printf("\n");
	mergeSort(unSortedValues,atoi(argv[3]));
	return 0;
}
//************END PROGRAM*************************
