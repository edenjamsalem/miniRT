/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:37:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/10 17:37:50 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	key_event(int keysym, t_mlx *mlx)
{
	if (keysym == ESC_KEY)
		close_window(mlx);
	return (0);
}

int	close_window(t_mlx *mlx)
{
	free_mem(mlx);
	exit(EXIT_SUCCESS);
}
