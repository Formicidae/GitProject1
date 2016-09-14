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
	int sum = 0;
	cout << "Rom is: " << rom << endl;
	//Checks every character in the roman numeral
	//Looks for each value in the tens place and for 4s and 9s checks after C, X or I
	for (int i = 0; i < rom.length(); i++)
	{
		if (rom[i] == 'M')
			sum += 1000;
		else if (rom[i] == 'D')
			sum += 500;
		else if (rom[i] == 'C' && (rom[i + 1] == 'M' || rom[i + 1] == 'D'))
			sum -= 100;
		else if (rom[i] == 'C')
			sum += 100;
		else if (rom[i] == 'L')
			sum += 50;
		else if (rom[i] == 'X' && (rom[i + 1] == 'L' || rom[i + 1] == 'C'))
			sum -= 10;
		else if (rom[i] == 'X')
			sum += 10;
		else if (rom[i] == 'V')
			sum += 5;
		else if (rom[i] == 'I' && (rom[i + 1] == 'V' || rom[i + 1] == 'X'))
			sum -= 1;
		else if (rom[i] == 'I')
			sum += 1;

        cout << "Sum: " << sum << endl;
	}
	return sum;
	//return 1234;
}

string convertToRoman(int num) {
    //Gets the number in the thousands, hundreds, tens and ones place
	string output = "";
	int thou = num / 1000;
	int hun = (num % 1000) / 100;
	int tens = ((num % 1000) % 100) / 10;
	int ones = (((num % 1000) % 100) % 10);

	//looks first for places that are less than 4
	//then checks for 4 and 5 nad adds those values
	//then adds any values greater than 5

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
	else if (hun == 4) {
		output += "CD";
	}
	else if (hun == 5) {
		output += "D";
	}
	else if (hun > 5 && hun < 9)
	{
	    output += "D";
		for (int i = 5; i < hun; i++)
		{
			output += "C";
		}
	}
	else if (hun == 9)
		output += "CM";

	if (tens > 0 && tens < 4) {
		for (int i = 0; i < tens; i++)
		{
			output += "X";
		}
	}
	else if (tens == 4)
	{
		output += "XL";
	}
	else if (tens == 5)
	{
		output += "L";
	}
	else if (tens > 5 && tens < 9)
	{
	    output += "L";
		for (int i = 5; i < tens; i++)
		{
			output += "X";
		}
	}
	else if(tens == 9){
		output += "XC";
	}
	if (ones > 0 && ones < 4) {
		for (int i = 0; i < ones; i++) {
			output += "I";
		}
	}
	else if (ones == 4)
	{
		output += "IV";
	}
	else if (ones == 5) {
		output += "V";
	}
	else if (ones > 5 && ones < 9) {
        output += "V";
		for (int i = 5; i < ones; i++)
		{
			output += "I";
		}
	}
	else if(ones == 9){
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
	bool last = false;
	char cline[24];
	//Opens file in input and output mode
	file.open("numbers.txt", ios::in | ios::out | ios::binary);
	//checks each ine if file isn't at it's end
	while(!file.eof())
    {
        getline(file, line);
        cout << line << endl;

        //file.seekg(-1,ios::cur);
        cout << "tell " << file.tellg() << endl;
        if(file.tellg() == -1){
            cout << "At last line";
            last = true;
        }
        //file.seekg(1,ios::cur);

        //Checks if line begins with space, if it does it's a Arabic line
        if(line[0] == ' ')
        {
            rom = "";
            cout << "It's a number" << endl;
            tmp = line.substr(16,20);
            stringstream myStream(tmp);
            myStream >> i;
            cout << i << endl;
            rom = convertToRoman(i);
            cout << rom << endl;
            line = rom + line.substr(rom.length(),20);
            cout << line << endl;

            if(last){
                file.close();
                file.open("numbers.txt", ios::in | ios::out | ios::binary);
                cout << "Final line N" << endl;
                cout << line << endl;
                file.seekg(-21,ios::end);
                file << endl;
                file << line;
                cout << line << endl;
                getline(file, line);
            }
            else{
                file.seekg(-22,ios::cur);
                file << line;
                getline(file, line);

            }

            //file.seekg(24,ios::cur);


        }
        else{
            cout << "Its Roman" << endl;
            stringstream s;
            s << convertToArabic(line.substr(0,16));
            line = line.substr(0,16) + s.str();
            cout << line << endl;
            file.seekg(-22,ios::cur);
            if(last){
                cout << "Final line R " << endl;
                //file << 'A';
                file.seekp(-22,ios_base::end);
            }
            file << line;
            getline(file, line);
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

