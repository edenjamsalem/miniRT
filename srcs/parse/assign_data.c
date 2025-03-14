/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:10 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 12:33:42 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	assign_rgb(t_rgb *colour, char *data)
{
	char	**rgb_str;
	int		rgb_int[3];
	int		num_elems;

	rgb_str = ft_split(data, ',');
	num_elems = ft_2darr_len((void **)rgb_str);
	if (num_elems != 3)
	{
		free_2darr((void **)rgb_str, num_elems);
		return (0);
	}
	rgb_int[0] = ft_atoi(rgb_str[0]);
	rgb_int[1] = ft_atoi(rgb_str[1]);
	rgb_int[2] = ft_atoi(rgb_str[2]);
	free_2darr((void **)rgb_str, 3);
	if (!rgb_in_range(rgb_int))
		return (0);
	colour->r = (unsigned char)rgb_int[0];
	colour->g = (unsigned char)rgb_int[1];
	colour->b = (unsigned char)rgb_int[2];
	return (1);
}

bool	assign_vector(t_vec3 *vector, char *data)
{
	char	**coords;
	int		num_elems;

	coords = ft_split(data, ',');
	num_elems = ft_2darr_len((void **)coords);
	if (num_elems != 3)
	{
		free_2darr((void **)coords, num_elems);
		return (false);
	}
	vector->x = ft_atof(coords[0]);
	vector->y = ft_atof(coords[1]);
	vector->z = ft_atof(coords[2]);
	free_2darr((void **)coords, 3);
	return (true);
}

bool	assign_material(t_surf *material, char *data)
{
	char	**properties;
	int		num_elems;
	int		i;

	properties = ft_split(data, ',');
	num_elems = ft_2darr_len((void **)properties);
	if (num_elems != 4)
		return (free_2darr((void **)properties, 4), false);
	i = -1;
	while (++i < 3)
	{
		((double *)material)[i] = ft_atof(properties[i]);
		if (!in_range(((double *)material)[i], 0.0, 1.0))
			return (free_2darr((void **)properties, 4), false);
	}
	((double *)material)[i] = ft_atof(properties[i]);
	free_2darr((void **)properties, 4);
	if (!in_range(material->exp, 0.0, 300.0))
		return (false);
	return (true);
}
