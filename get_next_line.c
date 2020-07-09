#include "get_next_line.h"

int		oversize_buf(char **p0, char **remem, char **tmp)
{
	**p0 = '\0';
	*tmp = *remem;
	if (!(*remem = ft_strdup(++(*p0))))
	{
		free(*remem);
		return (0);
	}
	free(*tmp);
	return (1);
}

void	remembered_buf(char ***line, char **p0, char **remem, char **tmp)
{
	if	((*p0 = ft_strchr(*remem, '\n')))
	{
		**p0 = '\0';
		*tmp = *line[0];
		*line[0] = ft_strjoin(*line[0], *remem);
		free(*tmp);
		oversize_buf(&*p0, &*remem, &*tmp);
	}
	else
	{
		*tmp = *line[0];
		*line[0] = ft_strjoin(*line[0], *remem);
		free(*tmp);
		*tmp = *remem;
		*remem = NULL;
		free(*tmp);
	}
}

int		return_val(char *p0, long readed, char **line)
{
	if (readed == -1 || !*line)
		return (-1);
	if (p0)
		return (1);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*remem;
	char		buf[BUFFER_SIZE + 1];
	long		readed;
	char		*p0;
	char		*tmp;

	p0 = NULL;
	readed = 0;
	if (!line || fd < 0 || BUFFER_SIZE < 1 || !(*line = malloc(1)))
		return (-1);
	*line[0] = 0;
	if (remem)
		remembered_buf(&line, &p0, &remem, &tmp);
	while (!p0 && (readed = read(fd, buf, BUFFER_SIZE)) > 0 && *line)
	{
		buf[readed] = '\0';
		if ((p0 = ft_strchr(buf, '\n')))
			if(!(oversize_buf(&p0, &remem, &tmp)))
				return (-1);
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (return_val(p0, readed, line));
}
