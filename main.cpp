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
	}
	return sum;

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
	//Opens file in input and output mode
	file.open("numbers.txt", ios::in | ios::out | ios::binary);
	//checks each ine if file isn't at it's end
	while(!file.eof())
    {
        //Gets the line for processing
        getline(file, line);

        //Checks if its at the end of file
        if(file.tellg() == -1){
            last = true;
        }
        //file.seekg(1,ios::cur);

        //Checks if line begins with space, if it does it's a Arabic line
        if(line[0] == ' ')
        {
            //Gets the number and convert the string to int
            rom = "";
            tmp = line.substr(16,20);
            stringstream myStream(tmp);
            myStream >> i;
            //Converts the int to roman and adds it to the beginning of the line
            rom = convertToRoman(i);
            line = rom + line.substr(rom.length(),20);

            //check if its on the last line
            if(last){
                //Reopens the file and moves from the last spot to the beginning of the last line
                file.close();
                file.open("numbers.txt", ios::in | ios::out | ios::binary);
                file.seekg(-21,ios::end);
                file << endl;
                file << line;
                getline(file, line);
            }
            else{
                //move to the beginning of the line and overlays it with the new one
                file.seekg(-22,ios::cur);
                file << line;
                getline(file, line);
            }
        }
        else{
            //If it's not a space it must be a Roman numeral
            //Grabs the beginning of the string for processing
            stringstream s;
            s << convertToArabic(line.substr(0,16));
            line = line.substr(0,16) + s.str();
            if(last){
                //If its at the end reopen the file
                file.close();
                file.open("numbers.txt", ios::in | ios::out | ios::binary);
                file.seekg(-21,ios::end);
                file << endl;
                file << line;
                getline(file, line);
            }
            else{
                //If its not at the end just move back to beginning of the line and overlay it with the new line
                file.seekg(-22,ios::cur);
                file << line;
                getline(file, line);
            }
        }
        //Checks if there are values on the next line
        //If not break the loop and end the program
        file.seekg(-1,ios::cur);
        if((int)file.peek() != 10){
            break;
        }
        file.seekg(1,ios::cur);
    }
    file.close();
    cout << "File processing complete.";
    return 0;
}

