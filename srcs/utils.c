/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:23:21 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/21 13:59:56 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	perror_exit(t_err err, int line_nbr, char **data, int i, t_scene *scene)
{
	ft_fprintf(2, "Error\n");
	if (err == LINE_ARG_COUNT)
		ft_fprintf(2, "Line %d: Incorrect number of args.\n", line_nbr);
	if (err == ARG_OUT_OF_RANGE)
		ft_fprintf(2, "Line %d: '%s' has invalid range.\n", line_nbr, data[i]);
	if (err == DUPLICATE)
		ft_fprintf(2, "Line %d: is duplicate.\n", line_nbr);
	if (err == MALLOC)
		ft_fprintf(2, "malloc error\n");
	
	free_arrlst(scene->objs, free);
	free_2darr((void **)data, ft_2darr_len((void **)data));
	exit(EXIT_FAILURE);
}
