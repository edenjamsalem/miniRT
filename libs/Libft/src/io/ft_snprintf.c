/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:22:39 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 19:39:16 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_print_hex(char *buffer, size_t size, unsigned int n,
				bool uppercase);
static int	ft_parse(char *buffer, size_t size, const char format,
				va_list args);
static int	ft_print_pointer(char *buffer, size_t size, void *ptr);

/*
Takes a format string and a variable number of arguments, formats them as
per the format string and writes the result to the buffer.

NOTE: The buffer only null-terminates if the buffer is large enough to hold it.
*/
int	ft_snprintf(char *buffer, size_t size, const char *format, ...)
{
	va_list	args;
	int		len;
	int		ret;
	size_t	pos;

	len = 0;
	pos = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
			ret = ft_parse(buffer + pos, size - pos, *++format, args);
		else
			ret = ft_putchar_buf(buffer + pos, size - pos, *format);
		if (ret == -1)
			return (-1);
		len += ret;
		pos += ret;
		format++;
	}
	if (pos < size)
		buffer[pos] = '\0';
	va_end(args);
	return (len);
}

static int	ft_parse(char *buffer, size_t size, const char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar_buf(buffer, size, va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr_buf(buffer, size, va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_buf(buffer, size, va_arg(args, int)));
	else if (format == 'u')
		return (ft_putunbr_buf(buffer, size, va_arg(args, unsigned int)));
	else if (format == 'X' || format == 'x')
		return (ft_print_hex(buffer, size, va_arg(args, unsigned int),
				format == 'X'));
	else if (format == 'p')
		return (ft_print_pointer(buffer, size, va_arg(args, void *)));
	else if (format == '%')
		return (ft_putchar_buf(buffer, size, '%'));
	else
		return (-1);
}

static int	ft_print_hex(char *buffer, size_t size, unsigned int n,
		bool uppercase)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_tobase(n, 16);
	if (!str)
		return (-1);
	if (uppercase)
		str = ft_strupr(str);
	len = ft_putstr_buf(buffer, size, str);
	free(str);
	return (len);
}

static int	ft_print_pointer(char *buffer, size_t size, void *ptr)
{
	int		len;
	char	*str;

	if (!ptr)
		return (ft_putstr_buf(buffer, size, "(nil)"));
	len = ft_putstr_buf(buffer, size, "0x");
	str = ft_tobase((unsigned long)ptr, 16);
	if (!str)
		return (-1);
	len += ft_putstr_buf(buffer + len, size - len, str);
	free(str);
	return (len);
}
