/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:01:11 by tuchikaw          #+#    #+#             */
/*   Updated: 2024/11/19 03:43:53 by tuchikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

char	*get_next_line(int fd);
char	*get_to_nr(char *static_char);
char	*get_to_next_newline(int fd, char *static_char);
char	*get_new_line(char *static_char);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_create_s1(char *s1);
char	*ft_strjoin(char *s1, char *s2);

#endif
