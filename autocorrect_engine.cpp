#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

int edits(const string& s1, const string& s2, int m, int n, map<pair<int,int>, int>& memo, int t)
{
	// string tab = "|       ";
	// string indent = "";
	// for(int i = 0; i < t; i++)
	// 	indent += tab;
	// cout << indent << "m, n = " << m << ", " << n << endl;
	// base cases
	if(m == 0 && n == 0) return 0;
	if(m == 0) return n;
	if(n == 0) return m;

	// check memo
	auto iter = memo.find(make_pair(m,n));
	if(iter != memo.end())
	{
		// cout << indent << "Found (" << m << ", " << n << ") in memo!" << endl;
		return iter->second;
	}

	// recurse
	int min_edits = 0;
	if(s1[m - 1] == s2[n - 1])
	{
		// cout << indent << "-- Continuing --" << endl;
		min_edits = edits(s1, s2, m - 1, n - 1, memo, t + 1); // last chars are same, punt the problem with one less char in each
	} else {
		// cout << indent << "-- Deleting --" << endl;
		int delete_val = edits(s1, s2, m - 1, n, memo, t + 1); // delete from s1
		// cout << indent << "-- Inserting --" << endl;
		int insert_val = edits(s1, s2, m, n - 1, memo, t + 1); // insert into s1 removing need for last char in s2
		// cout << indent << "-- Replacing --" << endl;
		int replace_val = edits(s1, s2, m - 1, n - 1, memo, t + 1); // replacing char in 
		min_edits = min({delete_val, insert_val, replace_val});
		min_edits++;
	}

	// cout << indent << "Optimal subproblem value: " << min_edits << endl;

	// memoize
	memo[make_pair(m,n)] = min_edits;

	// return
	// cout << indent << "Returning: " << min_edits << endl;
	return min_edits;
}

int edits(const string& s1, const string& s2)
{
	map<pair<int, int>, int> memo;
	return edits(s1, s2, s1.size(), s2.size(), memo, 0);
}

int main()
{
	ifstream wordsfile;
	string line;

	string word = "";
	while(word != "quit")
	{
		cout << "Enter word for suggestions: ";
		cin >> word;
		wordsfile.open("words.txt");

		if(wordsfile.is_open())
		{
			int min = 100;
			while(getline(wordsfile, line))
			{
				if(word[0] == line[0])
					if(edits(word, line) <= 1)
						cout << line << endl;
			}
		}

		wordsfile.close();

		cout << endl;
	}

	return 0;
}