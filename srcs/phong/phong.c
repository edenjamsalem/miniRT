/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:28:39 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/03 19:41:30by eamsalem         ###   ########.fr       */
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
	double	Kd = 0.9;
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

t_rgb	get_Is(t_light *light, t_intsec *intsec)
{
	double	Ks = 0.3;
	double	a = 200;
	double	specular_reflection;
	t_vec3	reflection;
	double	intensity;

	reflection = normalize(sub(light->pos, intsec->pos));
	specular_reflection = dot(reflection, intsec->normal);
	
	if (specular_reflection <= 0.0)
		return ((t_rgb){0, 0, 0});

	specular_reflection = pow(specular_reflection, a);
	intensity = light->brightness * Ks * specular_reflection;
	return (rgb_scale(light->colour, intensity));
}


t_rgb	phong(t_scene *scene, t_intsec *intsec)
{
	t_rgb	Ia;
	t_rgb	Id;
	t_rgb	Is;
	t_rgb	I;

	Ia = get_Ia(&scene->ambient_light);
	if (intsec->in_shadow)
		return (rgb_mult(intsec->colour, Ia));

	Id = get_Id(&scene->light_src, intsec);
	Is = get_Is(&scene->light_src, intsec);
	I = rgb_add(Ia, Id);
	I = rgb_add(I, Is);

	return (rgb_mult(intsec->colour, I));
}
