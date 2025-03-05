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
		get_light_data(scene, data, line_nbr);
	else if (ft_match(data[0], "sp"))
		get_sphere_data(scene, data, line_nbr);
	else if (ft_match(data[0], "pl"))
		get_plane_data(scene, data, line_nbr);
	else if (ft_match(data[0], "cy"))
		get_cylinder_data(scene, data, line_nbr);
}

bool	check_line(t_scene *scene, char **data, int line_nbr)
{
	static bool ambient_light;
	static bool camera;

	if (!data || !(*data))
		return (0);
	else if(ft_match(data[0], "A"))
	{
		if (ambient_light)
			perror_exit(DUPLICATE, line_nbr, data, 0, scene);
		ambient_light = true;
	}
	else if(ft_match(data[0], "C"))
	{
		if (camera)
			perror_exit(DUPLICATE, line_nbr, data, 0, scene);
		camera = true;
	}
	return (1);
}

void parse(char *file, t_scene *scene)
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
		data = ft_split_set(line, " \t\n");
		free(line);
		if (check_line(scene, data, line_nbr))
			extract_data(scene, data, line_nbr);
		free_2darr((void **)data, ft_2darr_len((void **)data));
		line = get_next_line(fd);
		line_nbr++;
	}
}
