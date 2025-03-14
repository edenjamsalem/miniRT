/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:04 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 11:16:05 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// returns an orthogonal vector to a and b
t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.z * b.x) - (a.x * b.z);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

t_vec3	normalize(t_vec3 a)
{
	return (scale(a, 1 / magnitude(a)));
}

void	print_vector(t_vec3 a)
{
	printf("x: %f, y: %f, z: %f\n", a.x, a.y, a.z);
}
