/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:33:48 by muabdi            #+#    #+#             */
/*   Updated: 2025/03/12 16:05:31 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static double    get_h(double t, t_ray *ray, t_cy *cylinder)
{
    t_vec3 p;
    double h;
    
    p = add(ray->origin, scale(ray->direction, t));
    h = dot(sub(p, cylinder->center), cylinder->normal);
    return (h);
}

static bool t_valid(double t, double h, t_cy *cylinder)
{
    return (t > 0 && h >= 0 && h <= cylinder->height);
}

static double  get_closest_curved_t(double t[2], t_ray *ray, t_cy *cylinder)
{
    double h1;
    double h2;

    h1 = get_h(t[0], ray, cylinder);
    h2 = get_h(t[1], ray, cylinder);

    if (t_valid(t[0], h1, cylinder) && t_valid(t[1], h2, cylinder))
        return fmin(t[0], t[1]);
    else if (t_valid(t[0], h1, cylinder))
        return t[0];
    else if (t_valid(t[1], h1, cylinder))
        return t[1];
    else
        return -1.0;
}

double get_curved_t(t_ray *ray, t_cy *cylinder)
{
    t_vec3 oc;
    double a, b, c, discriminant;
    double t[2];

    oc = sub(ray->origin, cylinder->center);
    a = 1 - pow(dot(ray->direction, cylinder->normal), 2);
    b = 2 * (dot(ray->direction, oc) - dot(ray->direction, cylinder->normal) * dot(oc, cylinder->normal));
    c = dot(oc, oc) - pow(dot(oc, cylinder->normal), 2) - pow(cylinder->diameter / 2.0, 2);
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1.0;

    t[0] = (-b - sqrt(discriminant)) / (2 * a);
    t[1] = (-b + sqrt(discriminant)) / (2 * a);

    return (get_closest_curved_t(t, ray, cylinder));
}

double get_top_t(t_ray *ray, t_cy *cylinder)
{
    double  t_pl;
    t_vec3  top_center_p;
    t_vec3  p_intsec;
    t_vec3  dist_from_center;
    
    top_center_p = add(cylinder->center, scale(cylinder->normal, cylinder->height));
    t_pl = dot(cylinder->normal, ray->direction);
    if (fabs(t_pl) < 0.000001) // checks if parallel
		return (-1);
	t_pl = dot(cylinder->normal, sub(top_center_p , ray->origin)) / t_pl;
    
    p_intsec = add(ray->origin, scale(ray->direction, t_pl));
    dist_from_center = sub(p_intsec, top_center_p);

    if (dot(dist_from_center, dist_from_center) <= (cylinder->radius * cylinder->radius))
        return (t_pl);
    return (-1);
}

double get_bottom_t(t_ray *ray, t_cy *cylinder)
{
    double  t_pl;
    t_vec3  p_intsec;
    t_vec3  dist_from_center;
    
    t_pl = dot(cylinder->normal, ray->direction);
    if (fabs(t_pl) < 0.000001) // checks if parallel
		return (-1);
	t_pl = dot(cylinder->normal, sub(cylinder->center , ray->origin)) / t_pl;
    
    p_intsec = add(ray->origin, scale(ray->direction, t_pl));
    dist_from_center = sub(p_intsec, cylinder->center);

    if (dot(dist_from_center, dist_from_center) <= (cylinder->radius * cylinder->radius))
        return (t_pl);
    return (-1);
}

double find_closest(double t_curved, double t_top, double t_bottom)
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
    intsec->t = find_closest(t_curved, t_top, t_bottom);
    if (intsec->t >= 0)
    {
        intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
        intsec->colour = cylinder->colour;
        intsec->normal = normalize(sub(intsec->pos, cylinder->center));
        intsec->obj = (void *)cylinder;
        intsec->properties = cylinder->properties;
    }
}
