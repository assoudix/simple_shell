#include "shell.h"

/**
 * _strcspn - Calculates the length of the initial segment of str1
 *            which consists entirely of characters not in str2
 * @str1: The string to search
 * @str2: The set of characters to reject
 *
 * Return: The length of the initial segment
 *         of str1 that does not contain
 *         any characters from str2
 */
size_t _strcspn(const char *str1, const char *str2)
{
	size_t i = 0, j;

	for (; str1[i]; i++)
	{
		for (j = 0; str2[j]; j++)
		{
			if (str1[i] == str2[j])
			{
				return (i);
			}
		}
		j = 0;
	}

	return (i);
}

/**
 * _strcmp - Compare two strings
 * @str1: The first string to compare
 * @str2: The second string to compare
 *
 * Return: An integer less than, equal to,
 *         or greater than zero if str1 is
 *         found to be less than, to match,
 *         or be greater than str2.
 */
int _strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}

	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);

	return (str1[i] - str2[i]);
}

/**
 * _strncmp - Compare two strings up to n characters
 * @str1: The first string to compare
 * @str2: The second string to compare
 * @n: The maximum number of characters to compare
 *
 * Return: An integer less than, equal to,
 *         or greater than zero if str1 is
 *         found, respectively, to be less than,
 *         to match, or be greater than str2.
 */
int _strncmp(char *str1, char *str2, int n)
{
	int i = 0;

	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}

	if (i == n)
		return (0);

	return (str1[i] - str2[i]);
}
