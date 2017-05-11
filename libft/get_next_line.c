/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 18:25:14 by fgallois          #+#    #+#             */
/*   Updated: 2017/04/27 12:34:45 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_line		*init_list(const int fd)
{
	t_line	*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new->fd = fd;
	new->line = ft_strnew(0);
	new->next = NULL;
	return (new);
}

static void			add_elem(t_line *list, t_line *new)
{
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = new;
	new->next = NULL;
}

static char			*get_first_line(t_line *list, char **line)
{
	char	*text;
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	text = list->line;
	while (text[i])
	{
		if (text[i] == EOL)
		{
			*line = ft_strsub(text, 0, i);
			tmp = text;
			text = ft_strdup(text + (i + 1));
			free(tmp);
			return (text);
		}
		i++;
	}
	*line = ft_strdup(text);
	ft_strclr(text);
	ft_strclr(list->line);
	return (text);
}

static int			read_file(int fd, t_line *list)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	tmp = NULL;
	ret = -42;
	while (!ft_strchr(list->line, EOL))
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		else if (ret == 0)
			return (0);
		buf[ret] = 0;
		tmp = list->line;
		if (!(list->line = ft_strjoin(list->line, buf)))
			return (-1);
		free(tmp);
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static	t_line		*file;
	int					ret;
	t_line				*tmp;

	if (!file)
		file = init_list(fd);
	tmp = file;
	if (fd < 0 || !line)
		return (-1);
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		if (tmp->next == NULL)
			add_elem(tmp, init_list(fd));
		tmp = tmp->next;
	}
	if ((ret = read_file(fd, tmp)) < 0)
		return (-1);
	tmp->line = get_first_line(tmp, line);
	if (!ft_strlen(tmp->line) && !ft_strlen(*line) && !ret)
		return (0);
	return (1);
}
