/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_curve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:09:11 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/12 17:15:28 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/miniRT.h"

static double    get_h(double t, t_ray *ray, t_cy *cylinder)
{
    t_vec3 p;
    double h;
    
    p = add(ray->origin, scale(ray->direction, t));
    h = dot(sub(p, cylinder->center), cylinder->axis);
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
    a = 1 - pow(dot(ray->direction, cylinder->axis), 2);
    b = 2 * (dot(ray->direction, oc) - dot(ray->direction, cylinder->axis) * dot(oc, cylinder->axis));
    c = dot(oc, oc) - pow(dot(oc, cylinder->axis), 2) - pow(cylinder->diameter / 2.0, 2);
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1.0;

    t[0] = (-b - sqrt(discriminant)) / (2 * a);
    t[1] = (-b + sqrt(discriminant)) / (2 * a);

    return (get_closest_curved_t(t, ray, cylinder));
}