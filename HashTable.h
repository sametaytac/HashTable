#ifndef _HashTable_H_
#define _HashTable_H_

#include <vector>
#include <string>

using namespace std;

enum hashTableType { LINEAR, QUADRATIC };

enum hashFunctionType { FUNC1, FUNC2 };

struct wordData
{
	int lineNumber;
	int wordNumber;
};

struct wordInText
{
	string name;
	vector<wordData> data;
};

class HashTable
{
	public:
 	      HashTable(hashTableType tType, hashFunctionType hType, const vector<wordInText>& words);
		void getWord(const string &name,vector<wordData>& wordResult, int &probingCount, double &accessTime);
		void getHashTablePerformance(double &averageProbingCount, double &averageAccessTime);
		int hashFunction(const string &key);
	private:
		vector<wordInText> hashTable;
		hashTableType tableType;
		hashFunctionType hashFuncType;

};


#endif
