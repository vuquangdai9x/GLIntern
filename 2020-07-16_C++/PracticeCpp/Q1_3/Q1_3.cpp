// Q1_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int n, char** args)
{
	printf("Number of Param %d\n", n);
	for (int i = 0; i < n; i++)
	{
		printf("param[%d] = %s\n", i, args[i]);
	}
	system("pause");
    return 0;
}

