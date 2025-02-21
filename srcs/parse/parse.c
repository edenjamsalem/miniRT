/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:20:08 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/21 13:51:16by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	extract_data(t_scene *scene, char **data, int line_nbr)
{
	if (ft_match(data[0], "A"))
		get_ambient_light_data(scene, data, line_nbr);
	else if (ft_match(data[0], "C"))
		get_camera_data(scene, data, line_nbr);
	else if (ft_match(data[0], "L"))
		get_light_src_data(scene, data, line_nbr);
	else if (ft_match(data[0], "sp"))
		get_sphere_data(scene, data, line_nbr);
	else if (ft_match(data[0], "pl"))
		get_plane_data(scene, data, line_nbr);
	else if (ft_match(data[0], "cy"))
		get_cylinder_data(scene, data, line_nbr);
}

bool parse_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**data;
	int		line_nbr;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	line_nbr = 1;
	while (line)
	{
		data = ft_split_set(line, " \t");
		free(line);
		extract_data(scene, data, line_nbr);
		free_2darr((void **)data, ft_2darr_len((void **)data));
		line = get_next_line(fd);
		line_nbr++;
	}
	return (1);
}
