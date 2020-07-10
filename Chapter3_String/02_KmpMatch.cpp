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

//show the string
void showstring(Str s)
{
	const char* c = s.ch;
	for (int i = 0; i < s.length; ++i)
	{
		cout << *c;
		++c;
	}
}

//substring match, bruteforce 
int forceMatch(Str mainStr, Str subStr)
{
	int i = 0;
	int j = 0;
	int k = i;    //k keeps the location of current matching

	while (i < mainStr.length && j < subStr.length)
	{
		if (mainStr.ch[i] == subStr.ch[j])
		{
			++i;
			++j;
		}
		else
		{
			i = ++k;
			j = 0;
		}
	}

	if (j >= subStr.length)
	{
		return k;
	}
	else
	{
		return 0;    //false
	}
}

//get the next array for KMP
void getNext(Str substr, int next[])
{
	int i = 0, j = -1;
	next[0] = -1;

	while (i < substr.length)    //just for understanding, array's actually out of bounds
	{
		if (j == -1 || substr.ch[i] == substr.ch[j])
		{
			++i;    //main string index move forward 
			++j;    //sub string index move forward
			next[i] = j;    //index j indicates the number of overlapping chars
		}
		else
		{
			j = next[j];    //relocate the j index, right after the max prefix string
		}
	}
}

//KMP match
int kmpMatch(Str mainStr, Str subStr, int next[])
{
	int i = 0,j = 0;

	while (i < mainStr.length && j < subStr.length)
	{
		if (j == -1 || mainStr.ch[i] == subStr.ch[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];    //relocate the j index
		}
	}

	if (j == subStr.length)
	{
		return i - j;
	}
	else
	{
		return 0;    //false
	}
}

int main()
{
	Str main_str,sub_str;
	strInit(main_str); strInit(sub_str);
	strAssign(main_str, "standbyme");

	strSub(sub_str, main_str, 2, 3);
	cout << "sub string of main string '";
	showstring(main_str);
	cout << "' is '";
	showstring(sub_str);
	cout << "'." << endl;

	int next[4];    //sub string's length +1
	getNext(sub_str, next);
	cout << "at location [" << kmpMatch(main_str, sub_str, next) << "] " << endl;

	return 0;
}

