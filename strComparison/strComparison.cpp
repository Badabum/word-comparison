
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <string>
#include "metaphone.h"
//#include <cctype>
#include <locale>
//#include <cwctype>
using std::string;
const char rus[] = "rus_rus.866";
const char eng[] = "";
void arrOut( double**array,int rows,int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns;j++)
		{
			std::cout << array[i][ j] << " ";
		}
		std::cout << std::endl;
	}
}

double StrComparison(std::string str1, std::string str2)
{
	str1 = " " + str1;
	str2 = " " + str2;
	const int rows = str1.length();
	const int columns = str2.length();
	const double maxLen = (str1.length() > str2.length()) ? str1.length() : str2.length();
	double **array = new double*[rows+1]; //matrix which contains all operations
	double cost = { 0 }, distance = { 0 };
	for (int i = 0; i < rows+1; i++)
	{
		array [i]= new double[columns+1];
	}
	for (int i = 0; i < rows + 1;i++)
	{
		for (int j = 0; j < columns + 1;j++)
		{
			array[i][j] = 0;
		}
	}
	for (int i = 0; i <str1.length()+1; i++)
		array[i][0] = i;
	for (int j = 0; j <str2.length()+1; j++)
		array[0][j] = j;
	for (int i = 1; i <=str1.length(); i++)
	{
		for (int j = 1; j <=str2.length();j++)
		{
			if (str1[i] == str2[j])
			{
				cost = 0;
			}
			else if (tolower(str1[i]) == tolower(str2[j]))
				cost = 0.5;
			else if (str1[i] != str2[j])
				cost = 1;
			array[i][j] = std::min({ array[i - 1][ j] + 1, array[i][ j - 1] + 1, array[i - 1][ j - 1] + cost });
			if ((i>1 && j>1) && (str1[i] == str2[j - 1] && str1[i - 1] == str2[j]))
				array[i][ j] = std::min({ array[i][j], array[i - 2][ j - 2] + cost });

		}
	}
	distance = array[str1.length()][ str2.length()];
	for (int i = 0; i < str1.length() + 1; i++)
		delete [] array[i];
	delete[]array;
	return (maxLen-distance)/maxLen;
}
double StrComparison(std::wstring str1, std::wstring str2)
{
	setlocale(LC_ALL, "");
	double addCost(0);
	std::wcout << str1 << " and " << str2 << std::endl;
	if (metaphone(str1)==metaphone(str2))
	{
		std::cout << "Soundnes" << std::endl;
		addCost = 0.01;

	}
	
	str1 = L" " + str1;
	str2 = L" " + str2;
	const int rows = str1.length();
	const int columns = str2.length();
	const double maxLen = (str1.length() > str2.length()) ? str1.length() : str2.length();
	double **array = new double*[rows + 1]; //matrix which contains all operations
	double cost = { 0 }, distance = { 0 };
	for (int i = 0; i < rows + 1; i++)
	{
		array[i] = new double[columns + 1];
	}
	for (int i = 0; i < rows + 1; i++)
	{
		for (int j = 0; j < columns + 1; j++)
		{
			array[i][j] = 0;
		}
	}
	for (int i = 0; i < str1.length() + 1; i++)
		array[i][0] = i;
	for (int j = 0; j < str2.length() + 1; j++)
		array[0][j] = j;
	for (int i = 1; i <= str1.length(); i++)
	{
		for (int j = 1; j <= str2.length(); j++)
		{
			
			if (str1[i] == str2[j])
			{
				cost = 0;
			}
			else if (towlower(str1[i]) == towlower(str2[j]))
			{
				cost = 0.2;

			}
				
			else if (towlower(str1[i]) != towlower(str2[j]))
			{
				cost = 1;
			}
				
			array[i][j] = std::min({ array[i - 1][j] + 1, array[i][j - 1] + 1, array[i - 1][j - 1] + cost });
			if ((i > 1 && j > 1) && (str1[i] == str2[j - 1] && str1[i - 1] == str2[j]))
				array[i][j] = std::min({ array[i][j], array[i - 2][j - 2] + cost });

		}
	}
	distance = array[str1.length()][str2.length()];
	for (int i = 0; i < str1.length() + 1; i++)
		delete[] array[i];
	delete[]array;
	double answer = (((maxLen - distance) / maxLen) >= 0.99)?(maxLen - distance) / maxLen : ((maxLen - distance) / maxLen) + addCost;
	return answer;
}

void main()
{
	setlocale(LC_ALL, "");
	using std::string;
	using std::cout; 
	std::wcin.imbue(std::locale("rus_rus.866"));
	std::string answer = "";
	do 
	{
		std::wstring wstr1 = L"";
		std::wstring wstr2 = L"";
		cout << "Enter string 1: ";
		getline(std::wcin, wstr1);
		cout << "Enter string 2: ";
		getline(std::wcin, wstr2);
		cout << "Try to calc wstrings:" << StrComparison(wstr1, wstr2) << std::endl;
		cout << "Continue?";
		getline(std::cin, answer);
	} while (answer!="No");
	
	system("pause");
}