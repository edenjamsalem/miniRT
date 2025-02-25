/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:00:17 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:36 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Outputs the string ’s’ to the given file descriptor followed by a newline.
int	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	ft_putchar_fd('\n', fd);
	return (ft_strlen(s) + 1);
}
