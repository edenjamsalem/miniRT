/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:24:35 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:20 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks for an printable character.
Returns a non-zero value if the character tests true and zero if it tests false.
*/
int	ft_isprint(int arg)
{
	if ((arg >= 32 && arg <= 126))
		return (16384);
	return (0);
}
