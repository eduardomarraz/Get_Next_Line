/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduamart <eduamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:52:52 by eduamart          #+#    #+#             */
/*   Updated: 2024/10/28 17:21:42 by eduamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H 
# define GET_NEXT_LINE_H 

# ifndef BUFFER_SIZE 	  // Significa "si no está definido", entonces asegura...
#	define BUFFER_SIZE 42 // asegura que BUFFER_SIZE solo se defina si no fue definido anteriormente.
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdio.h>

char	*update_line(char *str);
char	*extract_line(char *str);
char	*read_from_file(int fd, char *str);
char	*get_next_line(int fd);

// Funciones auxiliares
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);

#endif
