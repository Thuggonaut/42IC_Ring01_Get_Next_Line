#include <stdio.h>

size_t ft_strlen(const char *s)
{
    const char *start = s;
    while (*++s)
        ;
    return (s - start);
}


int main(void)
{
    printf("%d\n", ft_strlen("12345"));
    return (0);
}