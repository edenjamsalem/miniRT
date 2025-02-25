/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:24:35 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:28 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Returns an uppercase letter if the argument is a lowercase letter. Otherwise,
it returns the argument unchanged.
*/
int	ft_toupper(int ch)
{
	if (ch >= 97 && ch <= 122)
		return (ch -= 32);
	return (ch);
}
