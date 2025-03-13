/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:33:48 by muabdi            #+#    #+#             */
/*   Updated: 2025/03/12 17:27:58by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	camera_in_cy(t_cy *cy, t_camera *camera)
{
	t_vec3  to_camera;
    double  axis_project;
    t_vec3  radial_vec;
    
	to_camera = sub(camera->pos, cy->center);
    axis_project = dot(to_camera, cy->axis);
    if (axis_project < (cy->bottom_h) || axis_project > (cy->top_h))
        return false;
    
    radial_vec = sub(to_camera, scale(cy->axis, axis_project));
    return (dot(radial_vec, radial_vec) < cy->rad_sqr);
}

double get_top_t(t_ray *ray, t_cy *cy)
{
    double  t_pl;
    t_vec3  p_intsec;
    t_vec3  center_to_intsec;
    
    t_pl = dot(cy->axis, ray->dir);
    if (fabs(t_pl) < 0.000001) // checks if parallel
		return (-1);
	t_pl = dot(cy->axis, sub(cy->top_center , ray->origin)) / t_pl;
    if (t_pl < 0)
        return (-1);
    
    p_intsec = add(ray->origin, scale(ray->dir, t_pl));
    center_to_intsec = sub(p_intsec, cy->top_center);

    if (dot(center_to_intsec, center_to_intsec) <= (cy->rad_sqr))
    {
        cy->intsec_count += 1;
        return (t_pl);
    }
    return (-1);
}

double get_bottom_t(t_ray *ray, t_cy *cy)
{
    double  t_pl;
    t_vec3  p_intsec;
    t_vec3  center_to_intsec;
    
    t_pl = dot(cy->axis, ray->dir);
    if (fabs(t_pl) < 0.000001) // checks if parallel
		return (-1);
	t_pl = dot(cy->axis, sub(cy->bottom_center , ray->origin)) / t_pl;
    if (t_pl < 0)
        return (-1);
    
    p_intsec = add(ray->origin, scale(ray->dir, t_pl));
    center_to_intsec = sub(p_intsec, cy->bottom_center);

    if (dot(center_to_intsec, center_to_intsec) <= cy->rad_sqr)
    {
        cy->intsec_count += 1;
        return (t_pl);
    }
    return (-1);
}


t_vec3  get_intsec_normal(t_intsec *intsec, double t_top, double t_bottom, t_cy *cy)
{
    double  h;
    t_vec3  radial_center;

    if (intsec->t == t_top)
        return (cy->axis);
    else if (intsec->t == t_bottom)
        return(scale(cy->axis, -1));
    else
    {
        h = dot(sub(intsec->pos, cy->center), cy->axis);
        radial_center = add(cy->center, scale(cy->axis, h));
        return (normalize(sub(intsec->pos, radial_center)));
    }
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

void get_cy_intsec_data(t_ray *ray, t_cy *cy, t_intsec *intsec)
{
    double  t_curved;
    double  t_top;
    double  t_bottom;
    
    cy->intsec_count = 0;
    t_top = -1;
    t_bottom = -1;
    t_curved = get_curved_t(ray, cy);
    if (cy->intsec_count < 2)
        t_top = get_top_t(ray, cy);
    if (cy->intsec_count < 2)
        t_bottom = get_bottom_t(ray, cy);

    intsec->t = find_smallest(t_curved, t_top, t_bottom);
    if (intsec->t >= 0)
    {
        intsec->pos = add(ray->origin, scale(ray->dir, intsec->t));
        intsec->colour = cy->colour;
        intsec->normal = get_intsec_normal(intsec, t_top, t_bottom, cy);
        if (cy->camera_inside)
            intsec->normal = scale(intsec->normal, -1);
        intsec->obj = (void *)cy;
        intsec->surf = cy->surf;
    }
}
