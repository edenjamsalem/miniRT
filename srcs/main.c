/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:58 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 14:32:07 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int argc, char **argv)
{
	t_mlx			mlx;

	if (argc < 2 || argc > 4)
	{
		printf("Error\nInvalid number of arguments\n");
		return (EXIT_FAILURE);
	}
	parse(argv[1], &mlx.scene);
	init_project(&mlx, &mlx.scene, &mlx.scene.camera);
	if (argc > 2)
		mlx.scene.consts.rpp = min(abs(ft_atoi(argv[2])), 64);
	if (argc > 3)
		mlx.scene.consts.shadow_rpp = min(abs(ft_atoi(argv[3])), 128);
	render_scene(&mlx);
	mlx_hook(mlx.win, KEY_PRS_EVT, 1L << 0, key_event, &mlx);
	mlx_hook(mlx.win, DESTROY_EVT, 1L << 17, close_window, &mlx);
	mlx_loop(mlx.ptr);
}
