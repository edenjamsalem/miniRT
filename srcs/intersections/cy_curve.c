/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_curve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:09:11 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 16:59:30 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec3  get_radial_normal(t_vec3 p, t_cy *cylinder)
{
    double  h;
    t_vec3  radial_center;

    h = dot(sub(p, cylinder->center), cylinder->axis);
    radial_center = add(cylinder->center, scale(cylinder->axis, h));
    return (normalize(sub(p, radial_center)));
}

static double    get_h(double t, t_ray *ray, t_cy *cylinder)
{
    t_vec3 p;
    double h;
    
    p = add(ray->origin, scale(ray->dir, t));
    h = dot(sub(p, cylinder->center), cylinder->axis);
    return (h);
}

static bool t_valid(double t, double h, t_cy *cylinder)
{
    return (t > 0 && h >= (-cylinder->height / 2) && h <= (cylinder->height / 2));
}

static double  get_closest_t(double t[2], t_ray *ray, t_cy *cylinder)
{
    double h[2];

    h[0] = get_h(t[0], ray, cylinder);
    h[1] = get_h(t[1], ray, cylinder);

    if (t_valid(t[0], h[0], cylinder) && t_valid(t[1], h[1], cylinder))
        return fmin(t[0], t[1]);
    else if (t_valid(t[0], h[0], cylinder))
        return t[0];
    else if (t_valid(t[1], h[1], cylinder))
        return t[1];
    else
        return -1.0;
}

double get_curved_t(t_ray *ray, t_cy *cylinder)
{
    t_quadratic q;
    t_vec3  oc;
    double  t[2];

    oc = sub(ray->origin, cylinder->center);
    q.a = 1 - pow(dot(ray->dir, cylinder->axis), 2);
    q.b = 2 * (dot(ray->dir, oc) - dot(ray->dir, cylinder->axis) * dot(oc, cylinder->axis));
    q.c = dot(oc, oc) - pow(dot(oc, cylinder->axis), 2) - pow(cylinder->diameter / 2.0, 2);
    
    q.discriminant = (q.b * q.b) - (4 * q.a * q.c);
    if (q.discriminant < 0)
        return -1.0;

    t[0] = (-q.b - sqrt(q.discriminant)) / (2 * q.a);
    t[1] = (-q.b + sqrt(q.discriminant)) / (2 * q.a);

    return (get_closest_t(t, ray, cylinder));
}