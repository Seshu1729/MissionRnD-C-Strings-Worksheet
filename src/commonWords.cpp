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

//METHOD 1:

struct node
{
	struct node *Children;
	int ChildrenNumber;
	int start;
	int end;
};

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

void addWordToTree(struct node *root, char input[], int start, int end)
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
		incrementStart = root->Children[index].start;
		while (input[incrementStart] == input[start] && incrementStart<root->Children[index].end)
		{
			incrementStart++;
			start++;
		}
		if (incrementStart<root->Children[index].end)
		{
			addWordToTree(&root->Children[index], input, incrementStart, root->Children[index].end);
			root->Children[index].end = incrementStart;
			for (i = 0; i<root->Children[index].ChildrenNumber; i++)
				root->Children[index].Children[i].start = incrementStart;
		}
		if (start<end)
			addWordToTree(&root->Children[index], input, start, end);
	}
	else
	{
		root->ChildrenNumber++;
		root->Children = (struct node *)realloc(root->Children, (root->ChildrenNumber)*sizeof(struct node));
		root->Children[root->ChildrenNumber - 1].Children = NULL;
		root->Children[root->ChildrenNumber - 1].ChildrenNumber = 0;
		root->Children[root->ChildrenNumber - 1].start = start;
		root->Children[root->ChildrenNumber - 1].end = end;
	}
}

int searchString(struct node *root, char *str1, char *str2, int start, int end)
{
	int index, found = 0, i;
	for (index = 0; index<root->ChildrenNumber; index++)
	{
		if (str1[root->Children[index].start] == str2[start])
		{
			found = 1;
			break;
		}
	}
	if (found == 1)
	{
		root->Children[index].start;
		while (str1[root->Children[index].start] == str2[start] && root->Children[index].start<root->Children[index].end && start<end)
		{
			root->Children[index].start++;
			start++;
		}
		if (start == end)
			return 1;
		else if (start<end)
			return searchString(&root->Children[index], str1, str2, start, end);
	}
	return 0;
}

char **commonWords(char *str1, char *str2)
{
	char **result = NULL, *string;
	int NoOfCommonStrings = 0, start, index, returnValue;
	struct node root = { NULL, 0, 0, 0 };
	if (str1 == NULL || str2 == NULL)
		return NULL;
	for (index = 0; str1[index]; index++)
	{
		while (str1[index] && str1[index] == ' ')
			index++;
		start = index;
		while (str1[index] && str1[index] != ' ')
			index++;
		addWordToTree(&root, str1, start, index);
	}
	for (index = 0; str2[index]; index++)
	{
		while (str2[index] && str2[index] == ' ')
			index++;
		start = index;
		while (str2[index] && str2[index] != ' ')
			index++;
		returnValue = searchString(&root, str1, str2, start, index);
		if (returnValue == 1)
		{
			string = getString(str2, start, index);
			result = (char **)realloc(result, sizeof(char *)*(++NoOfCommonStrings));
			result[NoOfCommonStrings - 1] = string;
		}
	}	
	return result;
}

/*
METHOD 2:

struct node
{
	struct node *Children;
	int ChildrenNumber;
	int start;
	int end;
};

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

void addWordToTree(struct node *root, char input[], int start, int end)
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
		incrementStart = root->Children[index].start;
		while (input[incrementStart] == input[start] && incrementStart<root->Children[index].end)
		{
			incrementStart++;
			start++;
		}
		if (incrementStart<root->Children[index].end)
		{
			addWordToTree(&root->Children[index], input, incrementStart, root->Children[index].end);
			root->Children[index].end = incrementStart;
			for (i = 0; i<root->Children[index].ChildrenNumber; i++)
				root->Children[index].Children[i].start = incrementStart;
		}
		if (start<end)
			addWordToTree(&root->Children[index], input, start, end);
	}
	else
	{
		root->ChildrenNumber++;
		root->Children = (struct node *)realloc(root->Children, (root->ChildrenNumber)*sizeof(struct node));
		root->Children[root->ChildrenNumber - 1].Children = NULL;
		root->Children[root->ChildrenNumber - 1].ChildrenNumber = 0;
		root->Children[root->ChildrenNumber - 1].start = start;
		root->Children[root->ChildrenNumber - 1].end = end;
	}
}

int searchString(struct node *root, char *str1, char *str2, int start, int end)
{
	int index, found = 0, incrementStart, i;
	for (index = 0; index<root->ChildrenNumber; index++)
	{
		if (str1[root->Children[index].start] == str2[start])
		{
			found = 1;
			break;
		}
	}
	if (found == 1)
	{
		incrementStart = root->Children[index].start;
		while (str1[incrementStart] == str2[start] && incrementStart<root->Children[index].end && start<end)
		{
			incrementStart++;
			start++;
		}
		if (start == end)
			return 1;
		else if (start<end)
			return searchString(&root->Children[index], str1, str2, start, end);
	}
	return 0;
}

char **commonWords(char *str1, char *str2)
{
	char **result = NULL, *string;
	int NoOfCommonStrings = 0, start, index, returnValue;
	struct node root = { NULL, 0, 0, 0 };
	if (str1 == NULL || str2 == NULL)
		return NULL;
	for (index = 0; str1[index]; index++)
	{
		while (str1[index] && str1[index] == ' ')
			index++;
		start = index;
		while (str1[index] && str1[index] != ' ')
			index++;
		addWordToTree(&root, str1, start, index);
	}
	for (index = 0; str2[index]; index++)
	{
		while (str2[index] && str2[index] == ' ')
			index++;
		start = index;
		while (str2[index] && str2[index] != ' ')
			index++;
		returnValue = searchString(&root, str1, str2, start, index);
		if (returnValue == 1)
		{
			string = getString(str2, start, index);
			result = (char **)realloc(result, sizeof(char *)*(++NoOfCommonStrings));
			result[NoOfCommonStrings - 1] = string;
		}
	}	return result;
}

*/