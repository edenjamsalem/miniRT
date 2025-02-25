/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:38:45 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:32:40 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
Locates the first occurrence of the null-terminated string little in the string
big,where not more than len characters are searched. Characters that appear
after a ‘\0’ character are not searched.
*/
char	*ft_strnstr(const char *str, const char *sub, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*sub)
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == sub[j] && i + j < len)
		{
			if (!sub[j + 1])
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
