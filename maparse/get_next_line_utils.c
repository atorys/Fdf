#include "get_next_line.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*cpy;

	len = ft_strlen(str);
	i = 0;
	cpy = malloc(sizeof(char) * len + 1);
	if (cpy)
	{
		while (str[i])
		{
			cpy[i] = (char)str[i];
			i++;
		}
		cpy[i] = '\0';
		return (cpy);
	}
	return (NULL);
}

char	*ft_strchr(const char *s, char c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	unsigned int	i;
	char			*temp;

	i = 0;
	temp = (char *)s1;
	if (s1 == NULL)
		return (ft_strdup(s2));
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (*s1)
	{
		result[i++] = (char)*s1;
		s1++;
	}
	while (*s2)
	{
		result[i++] = (char)*s2;
		s2++;
	}
	result[i] = '\0';
	free(temp);
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	dest = malloc(sizeof(char) * len + 1);
	if (len >= 0 && dest)
	{
		while (len > 0 && s[start] != '\0' && start < ft_strlen(s))
		{
			dest[i] = s[start];
			len--;
			i++;
			start++;
		}
		dest[i] = '\0';
		return (dest);
	}
	return (NULL);
}
