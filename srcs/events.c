/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:26:57 by eamsalem          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/25 15:39:02 by muabdi           ###   ########.fr       */
=======
/*   Updated: 2025/02/24 13:34:48 by eamsalem         ###   ########.fr       */
>>>>>>> 425b374e70e650be43f9faf10d693366e9fedb32
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
