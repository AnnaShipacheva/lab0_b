#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

int cutWordsFromLine(string str, map <string, int> &table);
void inputMap(map <string, int> &table, int amountWords, ofstream& out);

int main (int argc, char* argv[])
{
	ifstream fileIn(argv[1]); 
	map <string, int> mapWords;
	int counterWords=0;

	while (!fileIn.eof()) 
	{
		string inputString;
		getline(fileIn, inputString);

		counterWords+=cutWordsFromLine(inputString, mapWords);
	}
	
	fileIn.close();
	ofstream fileOut(argv[2]);
	inputMap(mapWords, counterWords, fileOut);
	
	return 0;
}

void putInTable(string str, map <string, int> &table) {
	pair < map <string, int> ::iterator, bool> ret;
	ret = table.insert(pair <string, int>(str, 1));
	if (!ret.second) ret.first->second++;
}

int cutWordsFromLine(string str, map <string, int> &table) 
{
	unsigned int i = 0;
	unsigned int lenSubstr = 0;
	unsigned int start;
	int counter = 0;
	string buffer;

	while (i < str.length())
	{
		bool isDigit = (str[i] >= '0' && str[i] <= '9');
		bool isLetter = (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z');

		if ( isDigit || isLetter) 
		{
			if (lenSubstr == 0)
				start = i;
			++lenSubstr;
			++i;
		}
		else
		{
			if (lenSubstr != 0) {
				buffer = str.substr(start, lenSubstr);
				++counter;
				putInTable(buffer, table);
				lenSubstr = 0;
			}
			++i;
		}
	}
	if (lenSubstr != 0)
	{
		buffer = str.substr(start);
		++counter;
		putInTable(buffer, table);
	}
	return counter;
}

void inputMap(map<string, int> &table, int amountWords, ofstream& out) {
	while (!table.empty()) {
		map <string, int>::iterator it, maxIt;
		maxIt = table.begin();
		it = table.begin();
		while (it != table.end()) {
			if (it->second > maxIt->second)
				maxIt = it;
			++it;
		}
		double frequency = static_cast<double>(maxIt->second) / amountWords;
		out << maxIt->first << "," << frequency << ","<< frequency*100<<"%"<<"\n";
		table.erase(maxIt);
	}
}