/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blinn_phong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:37:31 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 16:52:47 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	get_Ia(t_light *ambient, double Ka)
{
	return (rgb_scale(ambient->colour, ambient->brightness * Ka));
}

t_rgb	get_diffuse_i(t_light *light, t_intsec *intsec, double Kd)
{
	double	diffuse;
	double	intensity;

	diffuse = dot(light->dir, intsec->normal);
	if (diffuse <= 0.0)
		return ((t_rgb){0, 0, 0});

	intensity = light->brightness * Kd * diffuse;
	return (rgb_scale(light->colour, intensity));
}

t_rgb	get_specular_i(t_light *light, t_intsec *intsec, t_vec3 view_dir, double Ks, double n)
{
	t_vec3	h;
	double	specular;
	double	intensity;
	
	h = normalize(add(light->dir, view_dir));
	specular = dot(intsec->normal, h);
	if (specular <= 0)
		return ((t_rgb){0, 0, 0});

	intensity = light->brightness * Ks * pow(specular, n);
	return (rgb_scale(light->colour, intensity));
}

t_rgb	get_lights_i(t_light **lights, t_intsec *intsec, t_vec3 view_dir)
{
	t_rgb	diffuse_i;
	t_rgb	specular_i;
	t_rgb	total_intensity;
	int		i;

	i = -1;
	total_intensity = (t_rgb){0, 0, 0};
	while (lights[++i])
	{
		if (lights[i]->visibility <= 0.0)
			continue ;
		diffuse_i = get_diffuse_i(lights[i], intsec, intsec->surf.Kd);
		specular_i = get_specular_i(lights[i], intsec, view_dir, intsec->surf.Ks, intsec->surf.n);
		
		diffuse_i = rgb_scale(diffuse_i, lights[i]->visibility);
		specular_i = rgb_scale(specular_i, lights[i]->visibility);

		total_intensity = rgb_add(total_intensity, diffuse_i);
		total_intensity = rgb_add(total_intensity, specular_i);
	}
	return (total_intensity);	
}

t_rgb	blinn_phong(t_scene *scene, t_intsec *intsec, t_vec3 view_dir)
{
	t_rgb	ambient_i;
	t_rgb	total_i;

	ambient_i = get_Ia(&scene->ambient_light, intsec->surf.Ka);
	if (intsec->in_shadow)
		return (rgb_mult(intsec->colour, ambient_i));

	total_i = rgb_add(ambient_i, get_lights_i((t_light **)scene->lights->content, intsec, view_dir));
	return (rgb_mult(intsec->colour, total_i));
}
