/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:26:57 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/25 16:09:31 by muabdi           ###   ########.fr       */
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
