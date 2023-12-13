#include "shell.h"

/**
 * _putchar - Write a character to the standard output (stdout)
 * @c: The character to write
 *
 * Return: On success, the character written.
 *         On error, -1 is returned.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - Write a string to the standard output (stdout)
 * @str: The string to write
 *
 * Return: The number of characters written
 */
int _puts(char *str)
{
	int i = 0;

	for (; str[i]; i++)
		_putchar(str[i]);

	write(1, "\n", 1);

	return (i);
}

/**
 * _strlen - Calculate the length of a string
 * @str: The string to calculate the length of
 *
 * Return: The length of the string
 */
int _strlen(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}

/**
 * _strcpy - Copy a string from src to dest
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: A pointer to the destination buffer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strcat - Concatenate two strings
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: A pointer to the destination buffer
 */
char *_strcat(char *dest, const char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}
