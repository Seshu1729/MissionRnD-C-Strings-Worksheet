/*
OVERVIEW: Given a string, reverse all the words not the string.

E.g.: Input: "i like coding". Output: "coding like i"

INPUTS: A string.

OUTPUT: Modify the string according to the logic.

NOTES: Don't create new string.
*/
#include <Stdio.h>
#include <string.h>

void swap(char *a, char *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void reverse(char *str, int beg, int end)
{
	while (beg<end)
		swap(&str[beg++], &str[end--]);
}

void str_words_in_rev(char *input, int len)
{
	int index = 0, beg;
	reverse(input, 0, len - 1);
	while (index<len)
	{
		while (input[index] == ' '&&index<len)
			index++;
		beg = index;
		while (input[index] != ' '&&index<len)
			index++;
		reverse(input, beg, index - 1);
		index++;
	}
}
