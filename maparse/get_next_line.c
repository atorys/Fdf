#include "get_next_line.h"

static int	ft_deviding(char *n, char **line, char **tail)
{
	size_t	len;
	char	*temp;

	len = 0;
	temp = *tail;
	while (temp[len] != '\n')
		len++;
	*line = ft_substr(*tail, 0, len);
	*tail = ft_strdup(++n);
	if (!*tail || !*line)
		return (-1);
	free(temp);
	return (1);
}

static int	ft_findintail(char **line, char **tail)
{
	char	*n;

	if (!*tail)
	{
		*line = ft_strdup("");
		if (!*line)
			return (-1);
		return (0);
	}
	n = ft_strchr(*tail, '\n');
	if (n)
		return (ft_deviding(n, line, tail));
	*line = ft_strdup(*tail);
	if (!*line)
		return (-1);
	free(*tail);
	*tail = NULL;
	return (0);
}

static int	ft_findinbuffer(int fd, char **line, char **the_n, char **tail)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;
	int		status;

	status = 0;
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (!bytes)
		return (2);
	if (bytes < 0)
		return ((int)bytes);
	buffer[bytes] = '\0';
	*the_n = ft_strchr(buffer, '\n');
	if (*the_n)
	{
		*the_n[0] = '\0';
		(*the_n)++;
		*tail = ft_strdup(*the_n);
		if (!*tail)
			return (-1);
		status = 1;
	}
	*line = ft_strjoin(*line, buffer);
	return (status);
}

int	get_next_line(int fd, char **line)
{
	static char	*tail = NULL;
	int			status;
	char		*the_n;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1 || line == NULL)
		return (-1);
	status = ft_findintail(line, &tail);
	the_n = NULL;
	while (!the_n && !status)
		status = ft_findinbuffer(fd, line, &the_n, &tail);
	if (status == 1)
		return (1);
	if (status == 2)
		return (0);
	return (-1);
}
