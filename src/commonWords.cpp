/*
OVERVIEW: Given two strings, find the words that are common to both the strings.
E.g.: Input: "one two three", "two three five".  Output: "two", "three".

INPUTS: Two strings.

OUTPUT: common words in two given strings, return 2D array of strings.

ERROR CASES: Return NULL for invalid inputs.

NOTES: If there are no common words return NULL.
*/

#include <stdio.h>
#include <malloc.h>

#define SIZE 31

struct node
{
	struct node *Children;
	int ChildrenNumber;
	int start;
	int end;
	int path;
};

int noOfSpaces(char *str)
{
	int value = 0;
	while (*str)
	{
		if (*str == ' ')
			value++;
		while (*str == ' ')
			str++;
		str++;
	}
	return value;
}

int stringLength(char input[])
{
	int length = -1;
	while (input[++length] != '\0');
	return length;
}

char *stringManage(char *input1, char extention1, char *input2, char extention2, int length1, int length2)
{
	char *Input;
	int i;
	Input = (char *)malloc(sizeof(char)*(length1 + length2 + 2));
	for (i = 0; i<length1; i++)
		Input[i] = input1[i];
	Input[i] = extention1;
	for (i = 0; i<length2; i++)
		Input[i + length1 + 1] = input2[i];
	Input[i + length1 + 1] = extention2;
	Input[length1 + length2 + 2] = '\0';
	return Input;
}

char *getString(char *input, int start, int end)
{
	int i, index = 0;
	char *result;
	result = (char *)malloc(end - start + 1);
	for (i = start; i<end; i++)
		result[index++] = input[i];
	result[index] = '\0';
	return result;
}

void addSuffix(struct node *root, char input[], int staticStart, int start, int end, int path, char **result, int *length)
{
	int index, found = 0, incrementStart, i;
	for (index = 0; index<root->ChildrenNumber; index++)
	{
		if (input[root->Children[index].start] == input[start])
		{
			found = 1;
			break;
		}
	}
	if (found == 1)
	{
		if (start == staticStart)
			staticStart = root->Children[index].start;
		incrementStart = root->Children[index].start;
		while (input[incrementStart] == input[start] && incrementStart<root->Children[index].end)
		{
			incrementStart++;
			start++;
		}
		if (incrementStart<root->Children[index].end)
		{
			addSuffix(&root->Children[index], input, staticStart, incrementStart, root->Children[index].end, path, result, length);
			root->Children[index].end = incrementStart;
			for (i = 0; i<root->Children[index].ChildrenNumber; i++)
				root->Children[index].Children[i].start = incrementStart;
		}
		if (start<end)
			addSuffix(&root->Children[index], input, staticStart, start, end, path, result, length);
		else if (path == 2 && incrementStart == root->Children[index].end)
		{
			result[*length] = getString(input, staticStart, root->Children[index].end);
			(*length)++;
		}
	}
	else
	{
		root->ChildrenNumber++;
		root->Children = (struct node *)realloc(root->Children, (root->ChildrenNumber)*sizeof(struct node));
		root->Children[root->ChildrenNumber - 1].Children = NULL;
		root->Children[root->ChildrenNumber - 1].ChildrenNumber = 0;
		root->Children[root->ChildrenNumber - 1].start = start;
		root->Children[root->ChildrenNumber - 1].end = end;
		root->Children[root->ChildrenNumber - 1].path = path;
	}
}

char **commonWords(char *str1, char *str2)
{
	char *input, **result;
	int index = 0, start, path = 1, length = 0, i;
	struct node root = { NULL, 0, 0, 0 };
	int length1, length2;
	int spaces1, spaces2;
	if (str1 == NULL || str2 == NULL)
		return NULL;
	length1 = stringLength(str1);
	length2 = stringLength(str2);
	spaces1 = noOfSpaces(str1);
	spaces2 = noOfSpaces(str2);
	result = (char **)malloc(sizeof(char *)*(spaces1<spaces2?spaces1:spaces2));
	input = stringManage(str1, '#', str2, '$', length1, length2);
	while (input[index])
	{
		while (input[index] == ' ')
			index++;
		start = index;
		while (input[index] != '\0'&&input[index] != '#'&&input[index] != '$'&&input[index] != ' ')
			index++;
		addSuffix(&root, input, start, start, index, path, result, &length);
		if (input[index] == '#')
			path = 2;
		index++;
	}
	if (length == 0)
		return NULL;
	return result;
}