#include "ss.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 */
void _putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}

/**
 * _puts - prints a string followed by a new line to stdout
 * @s: The string to print
 */
void _puts(const char *s)
{
    while (*s)
    {
        _putchar(*s);
        s++;
    }
    _putchar('\n');
}

/**
 * _strlen - returns the length of a string
 * @s: The string to measure
 *
 * Return: length of string
 */
size_t _strlen(const char *s)
{
    size_t len = 0;

    while (*s++)
    {
        len++;
    }
    return (len);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: difference of the two strings
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * _strncmp - compares at most the first n bytes of str1 and str2
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 *
 * Return: difference of the two strings
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
        n--;
    }
    return (n ? ((unsigned char)*s1 - (unsigned char)*s2) : 0);
}

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