/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:31 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 11:34:56 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	extract_data(t_parse *parse, t_scene *scene)
{
	if (!parse->data || !parse->data[0])
		return ;
	if (ft_match(parse->data[0], "A"))
		get_ambient_light_data(parse, scene);
	else if (ft_match(parse->data[0], "C"))
		get_camera_data(parse, scene);
	else if (ft_match(parse->data[0], "L"))
		get_light_data(parse, scene);
	else if (ft_match(parse->data[0], "sp"))
		get_sp_data(parse, scene);
	else if (ft_match(parse->data[0], "pl"))
		get_pl_data(parse, scene);
	else if (ft_match(parse->data[0], "cy"))
		get_cy_data(parse, scene);
}

void	parse(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	t_parse	parse;

	parse.scene = scene;
	scene->objs = init_arrlst(4);
	scene->lights = init_arrlst(4);
	fd = open(file, O_RDONLY);
	if (fd < 0 || invalid_extension(file))
		perror_exit(_FILE, &parse, 0);
	parse.line_num = 1;
	line = get_next_line(fd);
	while (line)
	{
		parse.data = ft_split_set(line, " \t\n");
		free(line);
		if (invalid_duplicate(&parse))
			perror_exit(DUPLICATE, &parse, 0);
		extract_data(&parse, scene);
		free_2darr((void **)parse.data, ft_2darr_len((void **)parse.data));
		line = get_next_line(fd);
		parse.line_num++;
	}
}
