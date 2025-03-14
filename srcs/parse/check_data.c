/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:17 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 12:21:30 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	rgb_in_range(int rgb[3])
{
	if (rgb[0] < 0 || rgb[0] > 255)
		return (0);
	if (rgb[1] < 0 || rgb[1] > 255)
		return (0);
	if (rgb[2] < 0 || rgb[2] > 255)
		return (0);
	return (1);
}

bool	in_range(double value, double lower, double higher)
{
	return (value >= lower && value <= higher);
}

bool	vector_in_range(t_vec3 *vector, double lower, double upper)
{
	if (!in_range(vector->x, lower, upper))
		return (0);
	if (!in_range(vector->y, lower, upper))
		return (0);
	if (!in_range(vector->z, lower, upper))
		return (0);
	return (1);
}

bool	invalid_duplicate(t_parse *parse)
{
	static bool	ambient_light;
	static bool	camera;

	if (!parse->data || !(*parse->data))
		return (0);
	if (ft_match(parse->data[0], "A"))
	{
		if (ambient_light)
			return (1);
		ambient_light = true;
	}
	else if (ft_match(parse->data[0], "C"))
	{
		if (camera)
			return (1);
		camera = true;
	}
	return (0);
}

bool	invalid_extension(char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (file[i] != 't' || file[i - 1] != 'r' || file[i - 2] != '.')
		return (1);
	return (0);
}
