/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:37:18 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/10 17:37:19 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static bool	rgb_in_range(int rgb[3])
{	
	if (rgb[0] < 0 || rgb[0] > 255)
		return (0);	
	if (rgb[1] < 0 || rgb[1] > 255)
		return (0);	
	if (rgb[2] < 0 || rgb[2] > 255)
		return (0);	
	return (1);
}

bool	assign_rgb(t_rgb *colour, char *data)
{
	char	**rgb_str;
	int		rgb_int[3];
	
	rgb_str = ft_split(data, ',');
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

bool	in_range(double value, double lower, double higher)
{
	return (value >= lower || value <= higher);
}

bool	vector_in_range(t_vec3 *vector, double lower, double upper)
{
	if (!in_range(vector->x, lower, upper))
		return(0);
	if (!in_range(vector->y, lower, upper))
		return(0);
	if (!in_range(vector->z, lower, upper))
		return(0);
	return (1);
}

void	assign_vector(t_vec3 *vector, char *data)
{
	char	**coords;

	coords = ft_split(data, ',');
	vector->x = ft_atof(coords[0]);
	vector->y = ft_atof(coords[1]);
	vector->z = ft_atof(coords[2]);
	free_2darr((void **)coords, 3);
}

bool	assign_material(t_material *material, char *data)
{
	char	**properties;

	properties = ft_split(data, ',');
	material->Ka = ft_atof(properties[0]);
	material->Kd = ft_atof(properties[1]);
	material->Ks = ft_atof(properties[2]);
	material->n = ft_atof(properties[3]);

	if (!in_range(material->Ka, 0.0, 1.0))
		return (0);
	if (!in_range(material->Kd, 0.0, 1.0))
		return (0);
	if (!in_range(material->Ks, 0.0, 1.0))
		return (0);
	if (!in_range(material->n, 0.0, 300.0))
		return (0);
	free_2darr((void **)properties, 4);
	return (1);
}