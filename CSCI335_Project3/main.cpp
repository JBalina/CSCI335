/*
Jonathan Balina
Pavel Shostak
CSCI 335
Project 3
*/

#include<iostream>
#include<fstream>
#include<string>
#include<unordered_set>
#include<set>
#include<vector>
#include<chrono>

using namespace std;
int main(int argc, char** argv)
{
	if(argc != 3)
		cout << "This program requires three arguments" << endl;
	ifstream infile1(argv[1]);
	ifstream infile2(argv[2]);
	if(!(infile1.is_open()))
	{
		cout << argv[1] << " could not be opened" << endl;
		return 0;
	}
	if(!(infile2.is_open()))
	{
		cout << argv[2] << " could not be opened" << endl;
		return 0;
	}
	ofstream outfile("output.txt");
	if(!(outfile.is_open()))
	{
		cout << "Output file cannot be opened" << endl;
		return 0;
	}
	
	unordered_set<string> dict;
	string word;
	while(infile2 >> word)
	{
		dict.insert(word);
	}
	vector<string> checkfile;
	string temp;
	//only recognizes letter characters, and converts all letters to lowercase
	while(getline(infile1,word))
	{
		temp = "";
		for(int i = 0; i < word.length(); i++)
		{
			if((word[i] >= 65) && (word[i] <= 90))//convert capital letters into lower case
			{
				word[i] += 32;
				temp += word[i];
			}
			else if((word[i] >= 97) && (word[i] <= 122))//normal letters
			{
				temp += word[i];
			}
			else//any nonletter character
			{
				if(temp != "")
					checkfile.push_back(temp);
				temp = "";
			}
		}
	}
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	for(int i = 0; i < checkfile.size(); i++)
	{
		
		if(dict.find(checkfile[i]) == dict.end())
		{
			outfile << checkfile[i] << "\t";
			unordered_set<string>::const_iterator search;
			for(search = dict.begin(); search != dict.end(); search++)
			{
				string dictword = *search;
				if(dictword.length() == checkfile[i].length())//for either one incorrect letter case, or swapped letters case
				{
					int count = 0; //count of how many letters do not match
					bool swapped = false;
					for(int j = 0; j < checkfile[i].length(); j++)
					{
						if(dictword[j] != checkfile[i][j])
						{
							count++;
							if(count > 2)//if more than two letters do not match, then it cannot be a single incorrect letter or two swapped letters
								break;
						}
						if((count == 2) && (dictword[j] == checkfile[i][j-1]) && (checkfile[i][j] == dictword[j-1]))
						{
							swapped = true;
						}
					}
					if(count == 1)
					{
						outfile << dictword << "\t";
					}
					if((swapped) && (count == 2))
					{
						outfile << dictword << "\t";
					}
				}
				else if(dictword.length() - checkfile[i].length() == 1)//missing one letter
				{
					int count = 0; //how many letters match
					for(int j = 0; j < checkfile[i].length(); j++)
					{
						if(checkfile[i][j] == dictword[j])
						{
							count++;
						}
						else
							break;
					}
					for(int j = checkfile[i].length() - 1; j >= 0; j--)
					{
						if(checkfile[i][j] == dictword[j+1])
						{
							count++;
						}
						else
							break;
					}
					if(count == checkfile[i].length())
					{
						outfile << dictword << "\t";
					}
				}
				else if(dictword.length() - checkfile[i].length() == -1)//one additional letter
				{
					int count = 0;
					for(int j = 0; j < dictword.length(); j++)
					{
						if(checkfile[i][j] == dictword[j])
						{
							count++;
						}
						else
							break;
					}
					for(int j = dictword.length() - 1; j >= 0; j--)
					{
						if(dictword[j] == checkfile[i][j+1])
						{
							count++;
						}
						else
							break;
					}
					if(count == dictword.length())
					{
						outfile << dictword << "\t";
					}
				}
			}
			outfile << "\n";
		}
	}
	auto t2 = chrono::steady_clock::now();
	cout << "Duration is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;

	infile1.close();//close files
	infile2.close();
}
