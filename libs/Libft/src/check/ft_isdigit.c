/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:24:35 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:19 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks for an digit character.
Returns a non-zero value if the character tests true and zero if it tests false.
*/
int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}
