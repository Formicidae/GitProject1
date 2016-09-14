// Project 1.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int convertToArabic(string rom) {
	int sum;
	for (int i = 0; i < rom.length(); i++)
	{
		if (rom[i] == 'M')
			sum += 1000;
		else if (rom[i] == 'D')
			sum += 500;
		else if (rom[i] == 'C' && (rom[i + 1] == 'M' || rom[i + 1] == 'D'))
			sum -= 100;
		else if (rom[i] = 'C')
			sum += 100;
		else if (rom[i] = 'L')
			sum += 50;
		else if (rom[i] == 'X' && (rom[i + 1] == 'L' || rom[i + 1] == 'C'))
			sum -= 10;
		else if (rom[i] = 'X')
			sum += 10;
		else if (rom[i] = 'V')
			sum += 5;
		else if (rom[i] == 'I' && (rom[i + 1] == 'V' || rom[i + 1] == 'X'))
			sum -= 1;
		else if (rom[i] = 'I')
			sum += 1;
	}
	//return sum;
	return 1234;
}

string convertToRoman(int num) {
	string output;
	int thou = num / 1000;
	int hun = (num % 1000) / 100;
	int tens = ((num % 1000) % 100) / 10;
	int ones = (((num % 1000) % 100) % 10) / 10;

	if (thou > 0 && thou <= 4)
	{
		for (int i = 0; i < thou; i++)
		{
			output += "M";
		}
	}
	if (hun > 0 && hun < 4)
	{
		for (int i = 0; i < hun; i++)
		{
			output += "C";
		}
	}
	else if (hun = 4) {
		output += "CD";
	}
	else if (hun = 5) {
		output += "D";
	}
	else if (hun > 5 && hun < 9)
	{
		for (int i = 5; i < hun; i++)
		{
			output += "C";
		}
	}
	else
		output += "CM";

	if (tens > 0 && tens < 4) {
		for (int i = 0; i < tens; i++)
		{
			output += "X";
		}
	}
	else if (tens = 4)
	{
		output += "XL";
	}
	else if (tens = 5)
	{
		output += "L";
	}
	else if (tens > 5 && tens < 9)
	{
		for (int i = 5; i < tens; i++)
		{
			output += "X";
		}
	}
	else {
		output += "XC";
	}
	if (ones > 0 && ones < 4) {
		for (int i = 0; i < ones; i++) {
			output += "I";
		}
	}
	else if (ones = 4)
	{
		output += "IV";
	}
	else if (ones = 5) {
		output += "V";
	}
	else if (ones > 5 && ones < 9) {
		for (int i = 5; i < ones; i++)
		{
			output += "I";
		}
	}
	else {
		output += "IX";
	}
	//return "TEST";
	return output;
}

int main()
{
    int num;
    int i;
    string rom;
	fstream file;
	string line;
	string tmp;
	char cline[24];
	file.open("numbers.txt", ios::in | ios::out | ios::binary);
	while(!file.eof())
    {
        getline(file, line);
        cout << line << endl;

        if(line[0] == ' ')
        {
            cout << "It's a number" << endl;
            tmp = line.substr(16,20);
            stringstream myStream(tmp);
            myStream >> i;
            rom = convertToRoman(i);
            cout << rom << endl;
            line = rom + line.substr(rom.length(),20);
            cout << line << endl;
            file.seekg(-22,ios::cur);
            file << line;
            //file.seekg(24,ios::cur);
            getline(file, line);

        }
        else{
            cout << "Its Roman" << endl;
        }



        file.seekg(-1,ios::cur);
        cout << (int)file.peek() << endl;
        if((int)file.peek() != 10){
            cout << "Breaking";
            break;
        }
        file.seekg(1,ios::cur);
        //cout << (int)file.peek() << endl;
    }
    file.close();
    return 0;
}
