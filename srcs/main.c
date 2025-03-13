/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:38:09 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 15:33:12 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int main(int argc, char **argv)
{
	t_mlx	mlx;
	struct timeval	start; // for testing only
	struct timeval	end;

	if (argc != 2)
		return (printf("Error: invalid number of arguments\n"), EXIT_FAILURE);
	gettimeofday(&start, NULL);

	parse(argv[1], &mlx.scene);
	init_project(&mlx, &mlx.scene);
	render_scene(&mlx);

	gettimeofday(&end, NULL);
	printf("time = %f\n", calc_time_diff(&start, &end) / 1000);

	mlx_hook(mlx.win, KEY_PRS_EVT, 1L << 0, key_event, &mlx);
	mlx_hook(mlx.win, DESTROY_EVT, 1L << 17, close_window, &mlx);
	mlx_loop(mlx.ptr);
}
