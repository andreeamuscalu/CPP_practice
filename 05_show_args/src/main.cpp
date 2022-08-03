#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("No program arguments found.\n");
		return 0;
	}

	for (int i = 1; i < argc; i++)
	{
		std::cout << "\n#" << argv[i] << std::endl;
	}
}