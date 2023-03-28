#include<stdio.h>
#include<stdlib.h>

int f1(char *str)
{
	printf("%c\n", str[0]);
	return 0;
}

int *f2(char *str)
{
	str = malloc(2);
	str[0]='a';
	str[1]='b';

	return 0;
}

int main()
{
	char *str = NULL;
	f2(str);
	f1(str);
	return 0;
}
