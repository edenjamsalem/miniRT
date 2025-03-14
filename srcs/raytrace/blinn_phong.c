/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blinn_phong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:37 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 11:55:11 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	get_i_ambient(t_light *ambient, double k_ambient)
{
	return (rgb_scale(ambient->colour, ambient->brightness * k_ambient));
}

t_rgb	get_diffuse(t_light *light, t_intsec *intsec, double k_diffuse)
{
	double	i_diffuse;
	double	intensity;

	i_diffuse = dot(light->dir, intsec->normal);
	if (i_diffuse <= 0.0)
		return ((t_rgb){0, 0, 0});
	intensity = light->brightness * k_diffuse * i_diffuse;
	return (rgb_scale(light->colour, intensity));
}

t_rgb	get_spec(t_light *light, t_intsec *intsec, t_vec3 view_dir)
{
	t_vec3	h;
	double	specular;
	double	intensity;
	double	spec_exponent;

	h = normalize(add(light->dir, view_dir));
	specular = dot(intsec->normal, h);
	if (specular <= 0)
		return ((t_rgb){0, 0, 0});
	spec_exponent = pow(specular, intsec->surf.n);
	intensity = light->brightness * intsec->surf.Ks * spec_exponent;
	return (rgb_scale(light->colour, intensity));
}

t_rgb	get_light_i(t_light **lights, t_intsec *intsec, t_vec3 view_dir)
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
		diffuse_i = get_diffuse(lights[i], intsec, intsec->surf.Kd);
		specular_i = get_spec(lights[i], intsec, view_dir);
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
	t_rgb	light_i;

	ambient_i = get_i_ambient(&scene->ambient_light, intsec->surf.Ka);
	if (intsec->in_shadow)
		return (rgb_mult(intsec->colour, ambient_i));
	light_i = get_light_i((t_light **)scene->lights->content, intsec, view_dir);
	total_i = rgb_add(ambient_i, light_i);
	return (rgb_mult(intsec->colour, total_i));
}
