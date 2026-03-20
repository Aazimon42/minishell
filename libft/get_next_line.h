/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:54:58 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/20 17:19:20 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	slen(const char *str);
char	*get_next_line(int fd);
ssize_t	ft_strchr_gnl(const char *str, int c, ssize_t nb_read);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(const char *src);
char	*ft_substr_gnl(char *s1, char *s2, size_t start, size_t len);

#endif
