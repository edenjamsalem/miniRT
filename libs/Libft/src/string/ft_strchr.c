/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:24:35 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:32:24 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Returns a pointer to the first occurrence of the character 'c' in the string 's'.
*/
char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' || (char)c == '\0')
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
