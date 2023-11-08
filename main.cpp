#include <iostream>
using namespace std;

#include "hw.hpp"

int main()
{

	char cmd_input = 0;
	while (cmd_input != 'q')
	{
		cout << "1: binarized\n"
			<< "2: 5 largest regions\n"
			<< "3: morphology\n"
			<< "q: quit\n"
			<< "Enter the question number to select output result: ";
		cin >> cmd_input;

		switch (cmd_input)
		{
		case '1':
			binarize();
			break;

		case '2':
			largest_regions();
			break;

		case '3':
			morphology();
			break;
		}

		cout << endl << endl;
	}
}
