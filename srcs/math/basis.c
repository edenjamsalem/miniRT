/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:36:48 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 15:38:25 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_world_basis(t_basis *world)
{
	world->right = (t_vec3){1, 0, 0};
	world->up = (t_vec3){0, 1, 0};
	world->forward = (t_vec3){0, 0, 1};
}

void	calc_local_basis(t_basis *local, t_vec3 forward, t_basis *world)
{
	local->forward = forward;
	if (dot(world->up, local->forward) >= 0.99)
		local->right = normalize(cross(world->forward, local->forward));
	else
		local->right = normalize(cross(world->up, local->forward));

	local->up = normalize(cross(local->forward, local->right));
}

t_vec3	transform_local_to_world(t_vec3 *ndc, t_basis *local)
{
	t_vec3	world_dir;

	world_dir.x = ndc->x * local->right.x + ndc->y * local->up.x + ndc->z * local->forward.x;
	world_dir.y = ndc->x * local->right.y + ndc->y * local->up.y + ndc->z * local->forward.y;
	world_dir.z = ndc->x * local->right.z + ndc->y * local->up.z + ndc->z * local->forward.z;
	return(world_dir);
}
