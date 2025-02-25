/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:56:27 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:35 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Outputs the character 'c' to the given file descriptor.
int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
