/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:22:39 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 18:30:09 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_print_hex(unsigned int n, bool uppercase);
static int	ft_print_pointer(void *ptr);
static int	ft_parse(const char format, va_list args);

/*
Takes a format string and a variable number of arguments,
	formats them as per the
format string and writes the result to the standard output.
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		ret;

	len = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
			ret = ft_parse(*++format, args);
		else
			ret = ft_putchar_fd(*format, 1);
		if (ret == -1)
			return (-1);
		len += ret;
		format++;
	}
	va_end(args);
	return (len);
}

static int	ft_parse(const char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (format == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (format == 'u')
		return (ft_putunbr_fd(va_arg(args, unsigned int), 1));
	else if (format == 'X' || format == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), format == 'X'));
	else if (format == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else if (format == '%')
		return (ft_putchar_fd('%', 1));
	else
		return (-1);
}

static int	ft_print_hex(unsigned int n, bool uppercase)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_tobase(n, 16);
	if (!str)
		return (-1);
	if (uppercase)
		str = ft_strupr(str);
	len = ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

static int	ft_print_pointer(void *ptr)
{
	int		len;
	char	*str;

	if (!ptr)
		return (ft_putstr_fd("(nil)", 1));
	len = ft_putstr_fd("0x", 1);
	str = ft_tobase((unsigned long)ptr, 16);
	if (!str)
		return (-1);
	len += ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
