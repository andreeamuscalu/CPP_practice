#include <iostream>

//(recursiva), calculeaza a^b
int power(int a, int b)
{
	if (b == 0)
		return 1;
	if (b % 2 == 0)
		return power(a, b / 2) * power(a, b / 2);
	return a * power(a, b / 2) * power(a, b / 2);
}

//calculeaza ordinul numarului intordus
int numberOrder(int a)
{
	int n = 0;
	while (a) {
		n++;
		a = a / 10;
	}
	return n;
}

bool isArmstrongNumber(int number)
{
	int n = numberOrder(number);
	int temp = number;
	int	sum = 0;

	while (temp) {
		int r = temp % 10;
		sum += power(r, n);
		temp = temp / 10;
	}
	return (sum == number);
}

void printIsArmstrong(int number)
{
	if (isArmstrongNumber(number))
	{
		std::cout << "Armstrong" << std::endl;
	}
	else
	{
		std::cout << "NOT Armstrong" << std::endl;
	}
}

bool checkIfNumber(const char* input)
{
	if (NULL == input || *input == '\0')
		return false;

	int countMinus = 0;
	while (*input)
	{
		char c = *input;
		switch (c)
		{
		case '-':
			if (++countMinus > 1)
				return false;
			break;
		default:
			if (c < '0' || c> '9')
				return false;
		}
		input++;
	}
	return true;
}

int main(int argc, char *argv[])
{
	// What is this program expected to do?
	// - Shows whether an argument is an armstrong number.
	// (what?)
	// -	An Armstrong number is a number that is equal to the sum of cubes of its digits.
	//		For example 0, 1, 153, 370, 371 and 407 are the Armstrong numbers.
	//		Let's try to understand why 153 is an Armstrong number:
	//			1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153
	//
	// How to launch it?
	// - Execute the binary and pass a parameter to it?
	// - E.g. Open CMD in bin/Debug or bin/Release
	//		  03_armstrong.exe 1		=> Output: Armstrong
	//		  03_armstrong.exe 2		=> Output: NOT Armstrong
	//		  03_armstrong.exe 			=> Output: No program arguments found.
	//		  03_armstrong.exe ABC		=> Undefined output (do whatever).
	//		  03_armstrong.exe 153		=> Output: Armstrong
	//		  03_armstrong.exe 154		=> Output: NOT Armstrong
	//

	// Make sure there are some program arguments available.
	if (argc <= 1)
	{
		std::cout << "No program arguments found." << std::endl;
		return 1;
	}

	int readNumber = 0;
	std::string argumentAsString = argv[1];
	const char* argumentAsCharArray = argumentAsString.c_str();


	if (checkIfNumber(argumentAsCharArray) == false)
	{
		printf("NAN\n");
	}
	else
	{
		readNumber = atoi(argumentAsCharArray);
		printIsArmstrong(readNumber);
	}
	
	return 0;
}