#ifndef METAPHONE_H_
#define METAPHONE_H_
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <locale>
#include <cwctype>

std::wstring metaphone(std::wstring str); //russian metaphone
template <typename T>
bool Contains(std::list<T> &lst, const T &mem) //checks if the list contains such member( T mem)
{
	for (std::list<T>::iterator it = lst.begin(); it !=lst.end(); it++)
	{
		if (*it == mem)
			return true;
	}
	return false;
}

bool Replace(std::wstring &str, const std::wstring &from, const std::wstring &to);//replace all "from" by "to"

std::wstring metaphone(std::wstring str) //returns metaphone code of the string;
{
	setlocale(LC_ALL, "");
	std::list<wchar_t> vowels = { L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�' };
	
	std::list <wchar_t> conson = { L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�' };
	std::list<wchar_t> sl_exclude = { L'�', L'�', L'�', L'�' };
	std::transform(str.begin(), str.end(), str.begin(),towupper);
	//std::wcout << "After transform" << str<<std::endl;

	std::wstring result = { str };
	//std::wcout << "result str: " << result << std::endl;
	Replace(result,L"��", L"�");
	Replace(result,L"��", L"�");
	Replace(result,L"��", L"�");
	Replace(result,L"��", L"�");

	Replace(result,L"�", L"�");
	Replace(result,L"�", L"�");
	Replace(result,L"�", L"�");
	Replace(result,L"�", L"�");

	Replace(result,L"�", L"�");
	Replace(result,L"�", L"�");
	Replace(result,L"�", L"�");
	Replace(result,L"�", L"�");
	//std::wcout << "After replacing" <<result<< std::endl;
	for (int i = 0; i < result.length() - 1; i++)
	{
		if (result[i]==result[i+1])
		{
			result = result.erase(i);
		}
	}
	/*std::cout << "After first if" << std::endl;*/
	for (int i = 0; i < result.length();i++)
	{
		auto letter = result[i];
		if (Contains(conson,letter)&&!Contains(sl_exclude,letter))
		{
			if ((i==result.length()-1)||(Contains(conson,result[i+1]))||iswpunct(result[i+1])||(iswspace(result[i+1])))
			{
				if (letter == L'�') result[i] = L'�';
				if (letter == L'�') result[i] = L'�';
				if (letter == L'�') result[i] = L'�';
				if (letter == L'�') result[i] = L'�';
				if (letter == L'�') result[i] = L'�';
			}
		}
	}
	//std::cout << "After second if" << std::endl;
	for (int i = 0; i < result.length() - 1;i++)
	{
		if (result[i] == result[i + 1])
			result.erase(i);
	}
	//std::cout << "After third if" << std::endl;
	Replace(result, L"��", L"�");
	Replace(result, L"��", L"�");
	return result;
}

bool Replace(std::wstring &str, const std::wstring &from, const std::wstring &to) 
{
	if (from.empty())
		return false;
	size_t start_pos(0);
	while ((start_pos = str.find(from, start_pos)) != std::wstring::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return true;
}

double tanimoto(std::string str1, std::string str2) //calculates tanimoto koefficient for two strings.
{
	std::cout << "Using tanimoto" << std::endl;
	int size = { 0 };
	double match(0);
	(str1.length() >= str2.length()) ? size = str2.length() : size = str1.length();
	for (int i = 0; i < size; ++i)
	{
		std::cout << str1[i] << " and " << str2[i] << std::endl;
		if (str1[i] == str2[i])
		{
			match++;
		}
		else if (tolower(str1[i]) == tolower(str2[i]))
		{
			match += 0.5;
		}
	}
	std::cout << "Match= " << match << std::endl;
	return  match / (str1.length() + str2.length() - match);
}

#endif
