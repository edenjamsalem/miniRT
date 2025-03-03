/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:28:39 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/03 18:22:14 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	get_Ia(t_light *ambient)
{
	double	Ka = 0.3;
	double	intensity;

	intensity = ambient->brightness * Ka;
	return (rgb_scale(ambient->colour, intensity));
}

t_rgb	get_Id(t_light *light, t_intsec *intsec)
{
	double	Kd = 0.3;
	double	diffuse_reflection;
	double	intensity;
	t_vec3	light_direction;
	
	light_direction = normalize(sub(light->pos, intsec->pos));
	diffuse_reflection = dot(light_direction, intsec->normal);
	if (diffuse_reflection <= 0.0)
		return ((t_rgb){0, 0, 0});

	intensity = light->brightness * Kd * diffuse_reflection;
	return (rgb_scale(light->colour, intensity));
}
/*
double	get_Is(t_light *light, t_intsec *intsec)
{
	double	Ks = 0.3;
	double	light_on_surface;
	t_vec3	reflection;

	reflection = normalize(sub(light->pos, intsec->pos));
	light_on_surface = dot(light_direction, intsec->normal);
	if (light_on_surface <= 0.0)
		return (0.0);
	else
		return (light->brightness * Ks * light_on_surface);
}
*/

t_rgb	phong(t_scene *scene, t_intsec *intsec)
{
	t_rgb	Ia;
	t_rgb	Id;
//	t_rgb	Is;

	Ia = get_Ia(&scene->ambient_light);
	if (intsec->in_shadow)
		return (Ia);
	Id = get_Id(&scene->light_src, intsec);
//	Is = get_Is(&scene->light_src, intsec);

	return (rgb_add(Ia, Id));
}
