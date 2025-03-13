/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:33:48 by muabdi            #+#    #+#             */
/*   Updated: 2025/03/12 17:27:58by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	camera_in_cy(t_cy *cylinder, t_camera *camera)
{
	t_vec3  to_camera;
    double  height_projection;
    double  radial_projection;
    t_vec3  radial_vec;
    
	to_camera = sub(camera->pos, cylinder->center);
    height_projection = dot(to_camera, cylinder->axis);
    if (height_projection < 0 || height_projection > cylinder->height)
        return false;
    
    radial_vec = sub(to_camera, scale(cylinder->axis, height_projection));
    radial_projection = magnitude(radial_vec);
    return (radial_projection > cylinder->radius);
}

double get_top_t(t_ray *ray, t_cy *cylinder)
{
    double  t_pl;
    t_vec3  top_center_p;
    t_vec3  p_intsec;
    t_vec3  dist_from_center;
    
    top_center_p = add(cylinder->center, scale(cylinder->axis, cylinder->height / 2));
    t_pl = dot(cylinder->axis, ray->direction);
    if (fabs(t_pl) < 0.000001) // checks if parallel
		return (-1);
	t_pl = dot(cylinder->axis, sub(top_center_p , ray->origin)) / t_pl;
    if (t_pl < 0)
        return (-1);
    
    p_intsec = add(ray->origin, scale(ray->direction, t_pl));
    dist_from_center = sub(p_intsec, top_center_p);

    if (dot(dist_from_center, dist_from_center) <= (cylinder->radius * cylinder->radius))
        return (t_pl);
    return (-1);
}

double get_bottom_t(t_ray *ray, t_cy *cylinder)
{
    double  t_pl;
    t_vec3  bottom_center_p;
    t_vec3  p_intsec;
    t_vec3  dist_from_center;
    
    bottom_center_p = add(cylinder->center, scale(cylinder->axis, (-cylinder->height / 2)));
    t_pl = dot(cylinder->axis, ray->direction);
    if (fabs(t_pl) < 0.000001) // checks if parallel
		return (-1);
	t_pl = dot(cylinder->axis, sub(bottom_center_p , ray->origin)) / t_pl;
    if (t_pl < 0)
        return (-1);
    
    p_intsec = add(ray->origin, scale(ray->direction, t_pl));
    dist_from_center = sub(p_intsec, bottom_center_p);

    if (dot(dist_from_center, dist_from_center) <= (cylinder->radius * cylinder->radius))
        return (t_pl);
    return (-1);
}

double find_smallest(double t_curved, double t_top, double t_bottom)
{
    double t;

    t = -1.0;
    if (t_curved > 0)
        t = t_curved;
    if (t_top > 0 && (t < 0 || t_top < t))
        t = t_top;
    if (t_bottom > 0 && (t < 0 || t_bottom < t))
        t = t_bottom;
    return (t);
}

void get_cy_intsec_data(t_ray *ray, t_cy *cylinder, t_intsec *intsec)
{
    double  t_curved;
    double  t_top;
    double  t_bottom;
    
    t_curved = get_curved_t(ray, cylinder);
    t_top = get_top_t(ray, cylinder);
    t_bottom = get_bottom_t(ray, cylinder);

	intsec->t = find_smallest(t_curved, t_top, t_bottom);

    if (intsec->t >= 0)
    {
        intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
        intsec->colour = cylinder->colour;
        intsec->normal = normalize(sub(intsec->pos, cylinder->center));

        if (intsec->t == t_top)
            intsec->normal = cylinder->axis;
        else if (intsec->t == t_bottom)
            intsec->normal = scale(cylinder->axis, -1);
        else
            intsec->normal = normalize(sub(intsec->pos, cylinder->center));

        if (cylinder->camera_inside)
            intsec->normal = scale(intsec->normal, -1);
        intsec->obj = (void *)cylinder;
        intsec->properties = cylinder->properties;
    }
}
