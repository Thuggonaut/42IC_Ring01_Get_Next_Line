#include <stdio.h>

char *ft_strchr(const char* str, int c) 
{
    while (*str != c)
        str++;
    if (*str == c) 
        return (char*)str;
    else 
        return (NULL);
}

int main() 
{
    char str[] = "Hello, world!";
    char* ptr = ft_strchr(str, 'o');
    if (ptr != NULL)
        printf("Found '%c' at position %ld.\n", *ptr, ptr - str);
    else 
        printf("Character not found.\n");
    return 0;
}