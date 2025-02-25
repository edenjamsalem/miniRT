/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:22:01 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:42 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*get_next_line_and_update(char **file_content_ptr);
static char	*append_read(char *file_content, char *buffer);
static void	*read_file(int fd, char **file_content);

/*
Reads a file line by line. It returns the line read or NULL if the file has been
completely read or an error occurred. It uses a static array to store and update
the file content after each read.
*/
char	*get_next_line(int fd)
{
	static char	*file_content[MAX_FD];
	char		*temp;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!file_content[fd])
	{
		file_content[fd] = malloc(1);
		if (!file_content[fd])
			return (NULL);
		file_content[fd][0] = '\0';
	}
	temp = read_file(fd, file_content);
	if (temp == NULL || file_content[fd][0] == '\0')
	{
		if (file_content[fd])
		{
			free(file_content[fd]);
			file_content[fd] = NULL;
		}
		return (NULL);
	}
	file_content[fd] = temp;
	return (get_next_line_and_update(&file_content[fd]));
}

static void	*read_file(int fd, char **file_content)
{
	char	*buffer;
	char	*new_str;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(file_content[fd]), NULL);
	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		new_str = append_read(file_content[fd], buffer);
		free(file_content[fd]);
		file_content[fd] = new_str;
	}
	free(buffer);
	return (file_content[fd]);
}

static char	*get_next_line_and_update(char **file_content_ptr)
{
	char	*line_end;
	char	*line;
	char	*new_str;

	line_end = ft_strchr(*file_content_ptr, '\n');
	if (!line_end)
		line_end = ft_strchr(*file_content_ptr, '\0');
	line = ft_substr(*file_content_ptr, 0, line_end - *file_content_ptr + 1);
	if (*line_end == '\n')
		new_str = ft_strdup(line_end + 1);
	else
		new_str = NULL;
	free(*file_content_ptr);
	*file_content_ptr = new_str;
	if ((!line || line[0] == '\0') && (!new_str || new_str[0] == '\0'))
	{
		if (line)
			free(line);
		if (new_str)
			free(new_str);
		*file_content_ptr = NULL;
		return (NULL);
	}
	return (line);
}

static char	*append_read(char *file_content, char *buffer)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(file_content) + ft_strlen(buffer)) + 1);
	if (!new_str)
	{
		free(file_content);
		return (NULL);
	}
	while (file_content && file_content[i])
	{
		new_str[i] = file_content[i];
		i++;
	}
	while (buffer && buffer[j])
	{
		new_str[i + j] = buffer[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}
