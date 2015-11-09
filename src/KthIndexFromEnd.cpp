/*
OVERVIEW: Given a string, return the Kth index from the end of the string.
E.g.: Input: "qwertyui", 3. Output: 't' (index starting from zero).

INPUTS: A string and value of K.

OUTPUT: Return the Kth index from the end of the string (index starting from zero).

ERROR CASES: Return '\0' for invalid inputs.

NOTES:
*/

char KthIndexFromEnd(char *str, int K)
{
	int length = 0;
	if (!str)
		return '\0';
	while (*str++)
		length++;
	if (length > K&&length>0)
	{
		while ((K--) != -2)
			str--;
		return *str;
	}
	return '\0';
}