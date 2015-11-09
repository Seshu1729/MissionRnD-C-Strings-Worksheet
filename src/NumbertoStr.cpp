/*
OVERVIEW: Given a float number ,Convert it into a string 

INPUTS: A Float,Final string ,How many digits after decimal has to be displayed .
Its zero for integers.


OUTPUT: No need to output anything ,Modify the str in function parameter such that it
now holds the string format of the float number specified

Example : number_to_str(345,str,0);
Should copy "345\0" in the str;
number_to_str(345.342,str,2);
Should copy "345.34" in the str;

NOTES: Don't create new string.

*/

#include <stdio.h>
#include<stdlib.h>

void number_to_str(float number, char *str, int afterdecimal)
{
	int temp = (int)number, length = 0, index;
	while (temp)
	{
		temp /= 10;
		length++;
	}
	if (number<0)
	{
		length++;
		str[0] = '-';
		number *= -1;
	}
	temp = (int)number;
	index = length - 1;
	while (temp)
	{
		str[index] = (temp % 10 + '0');
		index--;
		temp /= 10;
	}
	str[length] = '.';
	while (afterdecimal != -1)
	{
		temp = (int)(number * 10);
		str[++length] = (temp % 10 + '0');
		number *= 10;
		afterdecimal--;
	}
	str[length] = '\0';
}