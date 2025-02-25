/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:26:57 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/25 15:39:02 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	key_event(int keysym, t_mlx *mlx)
{
//	clear_img(mlx);
	if (keysym == ESC_KEY)
		close_window(mlx);
	// else if (keysym == A_KEY)
	// 	rotate('z', -2, &mlx->grid);
	// else if (keysym == D_KEY)
	// 	rotate('z', 2, &mlx->grid);
	// else if (keysym == W_KEY)
	// 	rotate('x', 2, &mlx->grid);
	// else if (keysym == S_KEY)
	// 	rotate('x', -2, &mlx->grid);
	// else if (keysym == Q_KEY)
	// 	rotate('y', -2, &mlx->grid);
	// else if (keysym == E_KEY)
	// 	rotate('y', 2, &mlx->grid);
	// else if (keysym == RIGHT_KEY)
	// 	shift_x(4, &mlx->grid);
	// else if (keysym == LEFT_KEY)
	// 	shift_x(-4, &mlx->grid);
	// else if (keysym == UP_KEY)
	// 	shift_y(-4, &mlx->grid);
	// else if (keysym == DOWN_KEY)
	// 	shift_y(4, &mlx->grid);
	return (0);
}

int	close_window(t_mlx *mlx)
{
	free_mem(mlx);
	exit(EXIT_SUCCESS);
}
