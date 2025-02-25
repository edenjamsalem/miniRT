/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:30:51 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 19:08:28 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// TODO: Move these to the appropriate c files (only include what is needed)
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

// Define maximum file descriptor
# ifndef MAX_FD
#  define MAX_FD 4096
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// String manipulation functions
char				*ft_strnstr(const char *str, const char *sub, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strstr(const char *str, const char *sub);
char				*ft_strtok(char *str, const char *delim);
char				*ft_strrchr(const char *str, int c);
char				*ft_strchr(const char *str, int c);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);
char				*ft_strrev(char *str);

// Character checking functions
int					ft_isprint(int arg);
int					ft_toupper(int ch);
int					ft_tolower(int ch);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);

// Conversion functions
char				*ft_tobase(unsigned long num, int base);
char				*ft_strupr(char *str);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);

// Memory manipulation functions
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memdup(const void *src, size_t size);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);

// I/O functions
int					ft_snprintf(char *buffer, size_t size, const char *format,
						...);
int					ft_putendl_buf(char *buffer, size_t size, const char *str);
int					ft_putstr_buf(char *buffer, size_t size, const char *str);
int					ft_putunbr_buf(char *buffer, size_t size, unsigned int n);
int					ft_putchar_buf(char *buffer, size_t size, char c);
int					ft_putnbr_buf(char *buffer, size_t size, int n);
int					ft_printf(const char *format, ...);
int					ft_putendl_fd(char *s, int fd);
int					ft_putstr_fd(char *s, int fd);
int					ft_putunbr_fd(int n, int fd);
int					ft_putchar_fd(char c, int fd);
int					ft_putnbr_fd(int n, int fd);
char				*get_next_line(int fd);

// Math functions
double				ft_clamp(double value, double min, double max);
double				ft_pow(double base, int exp);
double				ft_fmod(double x, double y);
double				ft_min(double x, double y);
double				ft_max(double x, double y);
double				ft_round(double x);
double				ft_trunc(double x);
double				ft_floor(double x);
double				ft_ceil(double x);
double				ft_sqrt(double x);
double				ft_abs(double x);

// List functions
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstadd_front(t_list **lst, t_list *new_list);
void				ft_lstadd_back(t_list **lst, t_list *new_list);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);

#endif // LIBFT_H