#include "hw4.cpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <cassert>
#include <ctype.h>
#include <algorithm>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{

	// I will use both your hw4.cpp and main.cpp file in grading !! 
	
	if(argc<2)
    	{
              cout << "usage : ./hw4 <file_name>" << endl;
              return 0;
    	}




ifstream inputFile;
vector<wordInText> worlds;
inputFile.open(argv[1]);
string sa,item;
int i=1,j=1;
while(getline(inputFile,sa))//sayfa sonuna kadar
{stringstream ss(sa);
j=1;
while (getline(ss, item, ' ')) { //boşluklara ayır
for(int k=0;k<item.length();k++)
{
if(isalnum(item[k])==false)//alnum olmayanları sil
{item.erase(item.begin()+k);
k--;}}
for(int k=0;k<item.length();k++)
item[k]=tolower(item[k]);//lower
if(item.length()!=0)
{
for(int k=0;k<worlds.size();k++){
if(item==worlds[k].name){

wordData a;
a.lineNumber=i;
a.wordNumber=j;
worlds[k].data.push_back(a);//lineları at
goto l;
}}


wordData a;
a.lineNumber=i;
a.wordNumber=j;
wordInText b;
b.name=item;
b.data.push_back(a);
worlds.push_back(b);
}
l:
 if(item.length())j++;}
i++; 
}
HashTable table1(LINEAR,FUNC1,worlds);

	return 0;
}
