/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:37:18 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/12 16:26:28 by muabdi           ###   ########.fr       */
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

bool	in_range(double value, double lower, double higher)
{
	return (value >= lower && value <= higher);
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

bool	assign_material(t_material *material, char *data)
{
	char	**properties;
	int		num_elems;

	properties = ft_split(data, ',');
	num_elems = ft_2darr_len((void **)properties);
	printf("num_elems = %d\n", num_elems);
	if (num_elems != 4)
	{
		free_2darr((void **)properties, num_elems);
		return (0);
	}

	material->Ka = ft_atof(properties[0]);
	material->Kd = ft_atof(properties[1]);
	material->Ks = ft_atof(properties[2]);
	material->n = ft_atof(properties[3]);

	printf("Ka = %f\n", material->Ka);
	printf("Kd = %f\n", material->Kd);
	printf("Ks = %f\n", material->Ks);
	printf("n = %f\n", material->n);

	if (!in_range(material->Ka, 0.0, 1.0))
		return (free_2darr((void **)properties, 4), false);
	if (!in_range(material->Kd, 0.0, 1.0))
		return (free_2darr((void **)properties, 4), false);
	if (!in_range(material->Ks, 0.0, 1.0))
		return (free_2darr((void **)properties, 4), false);
	if (!in_range(material->n, 0.0, 300.0))
		return (free_2darr((void **)properties, 4), false);
	free_2darr((void **)properties, 4);
	return (true);
}