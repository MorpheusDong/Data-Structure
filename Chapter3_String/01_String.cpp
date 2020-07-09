#include <iostream>

using namespace std;

typedef struct Str
{
	char* ch;
	int length;
}Str;

//string init
void strInit(Str& s)
{
	s.ch = NULL;
	s.length = 0;
}

//assign source string to dest string
int strAssign(Str& strDest, const char* ptrSrc)
{
	if (strDest.ch)
	{
		free(strDest.ch);    //clear dest string first
	}
	else
	{
		//do nothing
	}

	int len = 0;
	const char* c = ptrSrc;
	while (*c)    //calc the length of source string
	{
		++len;
		++c;
	}

	if (len == 0)
	{
		strDest.ch = NULL;    //no need to malloc
		strDest.length = 0;
		return 1;    //true
	}
	else
	{
		strDest.ch = (char*)malloc(sizeof(char) * (len + 1));
		if (strDest.ch == NULL)
		{
			return 0;    //false, malloc failed
		}
		else
		{
			c = ptrSrc;    //pointer reset
			for (int i = 0; i <= len; ++i, ++c)    //<= for '\0'
			{
				strDest.ch[i] = *c;
			}
			strDest.length = len;
			return 1;    //true
		}
	}
}

//compare two strings, result <0 means s1<s2
int strCompare(Str s1, Str s2)
{
	for (int i = 0; i < s1.length && i < s2.length; ++i)
	{
		if (s1.ch[i] != s2.ch[i])
		{
			return s1.ch[i] - s2.ch[i];
		}
		else
		{
			//do nothing
		}
	}
	return s1.length - s2.length;
}

//concat two strings to one
int strConcat(Str& strDest, Str s1, Str s2)
{
	if (strDest.ch)
	{
		free(strDest.ch);
		strDest.ch = NULL;
	}
	else
	{
		//do nothing
	}

	strDest.ch = (char*)malloc(sizeof(char) * (s1.length + s2.length + 1));
	if (strDest.ch == NULL)
	{
		return 0;    //false, malloc failed
	}
	else
	{
		int i;
		for (i = 0; i < s1.length; ++i)
		{
			strDest.ch[i] = s1.ch[i];
		}
		for (int j = 0; j <= s2.length; ++j)
		{
			strDest.ch[i + j] = s2.ch[j];
		}
		strDest.length = s1.length + s2.length;
		return 1;    //true
	}
}

//get the substring of source string
int strSub(Str& strDest, Str strSrc, int pos, int len)
{
	if (pos < 0 || pos >= strSrc.length || len<0 || len>strSrc.length - pos)
	{
		return 0;    //false
	}
	else
	{
		//do nothing
	}

	if (strDest.ch)
	{
		free(strDest.ch);
		strDest.ch = NULL;
	}
	else
	{
		//do nothing
	}

	if (len == 0)
	{
		free(strDest.ch);
		strDest.ch = NULL;
		return 1;    //true
	}
	else
	{
		strDest.ch = (char*)malloc(sizeof(char) * (len + 1));

		for (int i = 0,j = pos; j <= pos+len; ++i, ++j)    //<= for '\0'
		{
			strDest.ch[i] = strSrc.ch[j];
		}
		strDest.length = len;
		return 1;    //true
	}
}

//clear the string
void StrClear(Str& strDest)
{
	if (strDest.ch)
	{
		free(strDest.ch);
		strDest.ch = NULL;
	}
	else
	{
		// do nothing
	}
	strDest.length = 0;
}

//show the string
void showstring(Str s)
{
	const char* c = s.ch;
	for (int i = 0; i < s.length; ++i)
	{
		cout << *c;
		++c;
	}
	cout << endl;
}

int main()
{
	Str string_1,string_2,string_concat;
	strInit(string_1); strInit(string_2); strInit(string_concat);
	strAssign(string_1, "hello"); strAssign(string_2, ",there");
	strConcat(string_concat, string_1, string_2);
	showstring(string_concat);
	
	Str word_1, word_2,subword;
	strInit(word_1); strInit(word_2); strInit(subword);
	strAssign(word_1, "apprise"); strAssign(word_2, "abandon");
	cout << "apprise ";
	if (strCompare(word_1, word_2) > 0)
	{
		cout << ">";
	}
	else
	{
		cout << "<";
	}
	cout << " abandon\n";

	strSub(subword, word_1, 3, 4);
	cout << "one subword of 'apprise' is ";
	showstring(subword);

	return 0;
}

