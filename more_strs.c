#include "ss.h"

/**
 * _strdup - duplicates a string
 * @s: string to duplicate
 *
 * Return: pointer to the duplicated string or NULL if insufficient memory
 */
char *_strdup(const char *s)
{
	size_t len = _strlen(s) + 1;
	char *dup = malloc(len);

	if (dup)
	{
		memcpy(dup, s, len);
	}
	return (dup);
}

/**
 * _strcpy - copies the string pointed to by src to dest
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, const char *src)
{
	char *orig_dest = dest;

	while ((*dest++ = *src++))
		;
	return (orig_dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *orig_dest = dest;

	while (*dest)
	{
		dest++;
	}
	while ((*dest++ = *src++))
		;
	return (orig_dest);
}

/**
 * _strchr - locates the first occurrence of c in the string pointed to by s
 * @s: string to search in
 * @c: character to search for
 *
 * Return: pointer to the first occurrence of the character c in the string s,
 * or NULL if the character is not found
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (NULL);
}

