#include "LinkedList.h"
#include "Parser.h"
// #include "ArgumentManager.h"
#include <string>
#include <fstream>
#include <map>

using namespace std;

int main() 
{
	//ArgumentManager am(argc, argv);
	//string inputfile = am.get("input");
	//string outputfile = am.get("command");
	//string commandfile = am.get("output");
	
	string inputfile("input.txt");
	string outputfile("output.txt");
	string commandfile("command.txt");

	ifstream ifs(inputfile);
	ofstream ofs(outputfile);
	ifstream command(commandfile);

	LinkedList<string> list;
	map<string, string> m;
	string line;
	getline(ifs, line);
	char c = line[0];

	while (!ifs.eof()) 
	{
		getline(ifs, line);
		if (!line.empty() || line.length() != 0 || line != "")
		{
			if (m.find(line) == m.end())
			{
				m.insert({ line, line });
				switch (c)
				{
				case 'A': case 'a':
					list.insertByAlpha(line);
					break;
				case 'L': case 'l':
					list.insertByLength(line);
					break;
				case 'B': case 'b':
					list.insert(line);
					break;
				case 'E': case 'e':
					list.insertEnd(line);
					break;
				default:
					break;
				}
			}
		}
	}
	ifs.close();
	
	while (!command.eof())
	{
		getline(command, line);
		string sentence;
		int location;
		char c;
		c = line[0];

		switch (c) 
		{
		case 'A': case 'a':
			location = Parser::parseLocation(line);
			sentence = Parser::parseSentence(line);
			if(m.find(sentence) == m.end())
				list.add(location, sentence);
			break;
		case 'R': case'r':
			sentence = Parser::parseSentence(line);
			list.remove(sentence);
			break;
		case 'S': case 's':
			c = Parser::parseType(line);
			list.mergeSort(c == 'a' || c == 'A');
			break;
		default:
			break;
		}
	}
	command.close();

	list.output(ofs);
	ofs.close();
}