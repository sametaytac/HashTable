#include "HashTable.h"
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
#include <math.h>
#include <sys/time.h> 
using namespace std;
double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}




bool IsPrime(int number)
{
	
	int i;
	
	for (i=2; i<number; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	
	return true;	
}

int HashTable::hashFunction(const string &key){
int total=0;
if(hashFuncType==FUNC1)//func1
{
for(int i=0;i<key.length();i++)
{
total+=key[key.length()-i-1]*(int)pow(24,i);
}

while(total<0)
total+=hashTable.size();
return total%hashTable.size();
}
else{//func2
for(int i=0;i<key.length();i++)
{
total+=(int)key[key.length()-1-i]*(int)pow(37,i);
}
while(total<0)
total+=hashTable.size();
return total%hashTable.size();
}
}

HashTable::HashTable(hashTableType tType, hashFunctionType hType, const vector<wordInText>& words)
{
tableType=tType;
hashFuncType=hType;
int num,b;
num=words.size()*2;
while(IsPrime(num)==false)
num++;
hashTable.resize(num);//find size and resize
if(tableType==LINEAR)
{
for(int i=0;i<words.size();i++){
b=hashFunction(words[i].name);
while(hashTable[b].name.length()!=0)
{b++;
if(b==hashTable.size())
b=0;
}
hashTable[b].name=words[i].name;//put names
for(int k=0;k<words[i].data.size();k++){
wordData a;
a.lineNumber=words[i].data[k].lineNumber;
a.wordNumber=words[i].data[k].wordNumber;
hashTable[b].data.push_back(a);//put line and wordnumber

}

}
}

else{


for(int i=0;i<words.size();i++){//same with linear
b=hashFunction(words[i].name);
int y=b;
int c=1;
while(hashTable[y].name.length()!=0)
{
y=b+pow(c,2);
c++;
while(y>=hashTable.size())
y-=hashTable.size();
}
b=y;
hashTable[b].name=words[i].name;
for(int k=0;k<words[i].data.size();k++){
wordData a;
a.lineNumber=words[i].data[k].lineNumber;
a.wordNumber=words[i].data[k].wordNumber;
hashTable[b].data.push_back(a);
}
}
}
}




void HashTable::getWord(const string &name,vector<wordData>& wordResult, int &probingCount, double &accessTime){
while(wordResult.size()!=0)
wordResult.pop_back();
int b=hashFunction(name);
int y=b;
int a=0;
int c=1;
double start1, end1;
if(tableType==LINEAR)
{
start1 = get_wall_time();//start clock
while(hashTable[b].name.length()!=0)
{
a++;//probecount
if(hashTable[b].name==name)
break;
b++;
if(b==hashTable.size())
b=0;
}
if(hashTable[b].name.length()==0)
a++;
probingCount=a;
end1 = get_wall_time();
accessTime=end1-start1;
for(int i=0;i<hashTable[b].data.size();i++)//pushback lines
wordResult.push_back(hashTable[b].data[i]);
}
else
{//same with linear
start1 = get_wall_time();
while(hashTable[y].name.length()!=0)
{
a++;
if(hashTable[y].name==name)
break;
y=b+(int)pow(c,2);
c++;
while(y>=hashTable.size())
y-=hashTable.size();
}
if(hashTable[y].name.length()==0)
a++;
probingCount=a;
end1 = get_wall_time();
accessTime=end1-start1;
for(int i=0;i<hashTable[y].data.size();i++)
wordResult.push_back(hashTable[y].data[i]);
}
}

void HashTable::getHashTablePerformance(double &averageProbingCount, double &averageAccessTime)
{
double a;
double b=0;
double k=0;
double hum=0;
vector<string> sam;
for(int i=0;i<hashTable.size();i++){
if(hashTable[i].name.length()!=0)
sam.push_back(hashTable[i].name);
}
b=sam.size();
for(int i=0;i<b;i++){
int y=0;
double c=0;
vector<wordData> sa;
getWord(sam[i],sa,y,c);//call getword for every word
k+=y;//take probe
hum+=c;//take time
}
averageProbingCount=k/b;
averageAccessTime=hum/b;
}












