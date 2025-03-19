/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:36:48 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/19 16:35:34 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_world_basis(t_basis *world)
{
	world->right = (t_vec3){1, 0, 0};
	world->up = (t_vec3){0, 1, 0};
	world->fwd = (t_vec3){0, 0, 1};
}

void	calc_local_basis(t_basis *local, t_vec3 fwd, t_basis *world)
{
	local->fwd = fwd;
	if (dot(world->up, local->fwd) >= 0.99)
		local->right = normalize(cross(world->fwd, local->fwd));
	else
		local->right = normalize(cross(world->up, local->fwd));
	local->up = normalize(cross(local->fwd, local->right));
}

t_vec3	transform_basis(t_vec3 *ndc, t_basis *local)
{
	return ((t_vec3){
		ndc->x * local->right.x + ndc->y * local->up.x + ndc->z * local->fwd.x,
		ndc->x * local->right.y + ndc->y * local->up.y + ndc->z * local->fwd.y,
		ndc->x * local->right.z + ndc->y * local->up.z + ndc->z * local->fwd.z
	});
}
