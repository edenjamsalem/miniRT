/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:24:35 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Returns a lowercase letter if the argument is an uppercase letter. Otherwise,
it returns the argument unchanged.
*/
int	ft_tolower(int ch)
{
	if (ch >= 65 && ch <= 90)
		return (ch += 32);
	return (ch);
}
