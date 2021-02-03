#pragma once

#include <string>

class Parser 
{
public:
	static int parseLocation(std::string s)
	{
		unsigned first = s.find("(");
		unsigned last = s.find(")");
		std::string str = s.substr(first + 1, (last - first) - 1);
		return stoi(str);
	}
	static std::string parseSentence(std::string s)
	{
		unsigned first = s.find("[");
		unsigned last = s.find("]");
		return s.substr(first + 1, (last - first) - 1);
	}
	static char parseType(std::string s)
	{
		unsigned first = s.find("(");
		unsigned last = s.find(")");
		std::string str = s.substr(first + 1, (last - first) - 1);
		return str[0];
	}
};
