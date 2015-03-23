#ifndef _WIND_STRINGS_H_
#define _WIND_STRINGS_H_
#include <string>
#include <list>

namespace wind
{

class Strings 
{
private:

public:
	static bool IsPalindrome (std::string str)
	{
		int f = 0;
		int b = str.size() - 1;
		while (f != b && !(f > b))
		{
			if (str[f] != str[b]) return false;
			f++;
			b--;
		}
		return true;
	}

	static std::list<std::string> * Split (std::string original, char separator)
	{
		std::list<std::string> * substrings = new std::list<std::string> ();
		std::string str = "";
		for (std::string::iterator sit = original.begin(); sit != original.end(); sit++)
		{
			char c = *sit;
			if (c == separator)
			{
				substrings->push_back(str);
				str = "";
			}
			else
			{
				str += std::string(1, c);
			}
		}
		// Get the last element
		if (str.size() > 0)
		{
			substrings->push_back(str);
		}
		return substrings;
	}
};

}
#endif
