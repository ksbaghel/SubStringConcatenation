// SubStringConcatenation.cpp : Defines the entry point for the console application.
/*
You are given a string, S, and a list of words, L, that are all of the same length.

Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.

Example :

S: "barfoothefoobarman"
L: ["foo", "bar"]
You should return the indices: [0,9].
(order does not matter).

*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool isValidConcateStr(string& s, int word_size, unordered_map<string, int> &wordCount)
{
	//Now check if each word of word_size in sub_str appears exactly as wordCount
	unordered_map<string, int> seenWord;
	int len = s.length();
	for (int i = 0; i <= len - word_size; i += word_size)
	{
		string currWord = s.substr(i, word_size);
		if (wordCount.find(currWord) == wordCount.end()) return false;

		if (seenWord.find(currWord) != seenWord.end())
		{
			seenWord[currWord]++;
		}
		else {
			seenWord[currWord] = 1;
		}

		if (seenWord[currWord] > wordCount[currWord]) return false;
	}

	return true;
}

vector<int> getConcatedString(string& s, vector<string>& wordList)
{
	vector<int> res;

	int n = wordList.size();
	if (n == 0) return res;

	int str_len = s.length();
	int word_size = wordList[0].length();
	if (str_len < word_size*n) return res;

	unordered_map<string, int> wordCount;
	string concatStr = "";
	for (int i = 0; i < n; i++)
	{
		concatStr += wordList[i];
		if (wordCount.find(wordList[i]) != wordCount.end())
		{
			wordCount[wordList[i]]++;
		}
		else {
			wordCount[wordList[i]] = 1;
		}
	}

	//Now sort the concatedstr
	sort(concatStr.begin(), concatStr.end());

	int len = concatStr.length();
	//Now take a substring of length len from each starting pos in S and compare it with concatedString.
	for (int i = 0; i <= str_len - len; i++)
	{
		string substr = s.substr(i, len);
		sort(substr.begin(), substr.end());

		if (substr.compare(concatStr) == 0) //could be a possible match
		{
			if (isValidConcateStr(s.substr(i, len), word_size, wordCount))
			{
				res.push_back(i);
			}
		}
	}

	return res;
}

int main()
{
	string s;
	cin >> s;

	int n;
	cin >> n;

	vector<string> wordList(n);
	for (int i = 0; i < n; i++)
	{
		cin >> wordList[i];
	}

	vector<int> res = getConcatedString(s, wordList);

	for (int i = 0; i < res.size(); i++)
	{
		int len = n*(wordList[0].size());
		cout << res[i] << " : " << s.substr(res[i], len) << endl;
	}

    return 0;
}

