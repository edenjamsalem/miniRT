/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blinn_phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:28:39 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/03 19:41:30by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	get_Ia(t_light *ambient, double Ka)
{
	return (rgb_scale(ambient->colour, ambient->brightness * Ka));
}

t_rgb	get_Id(t_light *light, t_intsec *intsec, double Kd)
{
	double	diffuse;
	double	intensity;

	diffuse = dot(light->dir, intsec->normal);
	if (diffuse <= 0.0)
		return ((t_rgb){0, 0, 0});

	intensity = light->brightness * Kd * diffuse;
	return (rgb_scale(light->colour, intensity));
}

t_rgb	get_Is(t_light *light, t_intsec *intsec, t_vec3 view_dir, double Ks, double n)
{
	t_vec3	H;
	double	specular;
	double	intensity;
	
	H = normalize(add(light->dir, view_dir));
	specular = dot(intsec->normal, H);
	if (specular <= 0)
		return ((t_rgb){0, 0, 0});

	intensity = light->brightness * Ks * pow(specular, n);
	return (rgb_scale(light->colour, intensity));
}

t_rgb	blinn_phong(t_scene *scene, t_intsec *intsec, t_vec3 view_dir)
{
	t_rgb	Ia;
	t_rgb	Id;
	t_rgb	Is;
	t_rgb	I;

	Ia = get_Ia(&scene->ambient_light, intsec->properties.Ka);
	if (intsec->in_shadow)
		return (rgb_mult(intsec->colour, Ia));
	
	scene->light.dir = normalize(sub(scene->light.pos, intsec->pos));
	Id = get_Id(&scene->light, intsec, intsec->properties.Kd);
	Is = get_Is(&scene->light, intsec, view_dir, intsec->properties.Ks, intsec->properties.n);
	I = rgb_add(Ia, Id);
	I = rgb_add(I, Is);

	return (rgb_mult(intsec->colour, I));
}
