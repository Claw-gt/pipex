# libft

|**Name of the program** |**Files**|**Description**|
| ------- | ------- | ------ |
| libft.a | Makefile, libft.h , ft_*.c|Make your own library |

## Parte 1 - Funciones de libc

| Function | Prototype | Return value | Description |
|--------- | ----------- | ------- | ------ |
|`ft_isalpha` | | | |
|`ft_isdigit` | | | |
|`ft_isalnum` | | | |
|`ft_isascii` | | | |
|`ft_isprint` | | | |
|`ft_strlen` | | | |
|`ft_memset` | | | |
|`ft_bzero` | | | |
|`ft_memcpy` | | | |
|`ft_memmove` | | | |
|`ft_strlcpy` | | | |
|`ft_strlcat` | | | |
|`ft_toupper` | | | |
|`ft_tolower` | | | |
|`ft_strchr` | | | |
|`ft_strrchr` | | | |
|`ft_strncmp` | | | |
|`ft_memchr` | | | |
|`ft_memcmp` | | | |
|`ft_strnstr` | | | |
|`ft_atoi` | | | |
|`ft_calloc` | | | |
|`ft_strdup` | | | |

## Parte 2 - Funciones adicionales

| Function | Prototype | Return value | Description |
|--------- | ----------- | ------- | ------ |
|`ft_substr`|`char *ft_substr(char const *s, unsigned int start, size_t len);`| Substring. NULL if dynamic allocation fails| Allocate (with malloc(3)) and return a substring of string 's'. It will start from 'start' and have a maximum length of 'len'|
|`ft_strjoin`|`char *ft_strjoin(char const *s1, char const *s2);`| New string. NULL if dynamic allocation fails| Allocate (with malloc(3)) and return a new string formed by concatenation between 's1' and 's2'|
|`ft_strtrim`|`char *ft_strtrim(char const *s1, char const *set);`| Trimmed string. NULL if dynamic allocation fails| Delete all characters of string 'set' from the beginning and from the end until finding a character not belonging to 'set'|
|`ft_split`|`char **ft_split(char const *s, char c);`| Array of new strings resulted from the split. NULL if dynamic allocation fails| Allocate an array of strings resulted from splitting string 's' on substrings with character 'c' as delimiter|
