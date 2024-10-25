/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduamart <eduamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:15:51 by eduamart          #+#    #+#             */
/*   Updated: 2024/10/25 15:13:41 by eduamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/**
 * @brief Combines two strings, s1 and s2, into a single new string.
 * If s1 is NULL, it creates a new empty string. Frees the memory of s1
 * after concatenation.
 * 
 * @param s1 The first string to be concatenated.
 * @param s2 The second string to be concatenated to s1.
 * @return Returns a pointer to the new combined string,
 * or NULL if there is an error.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

		if (!s1)  // Si s1 es NULL, inicializarlo como una cadena vacía
    {
        s1 = malloc(1);
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }

	joined = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char)); // Se calcula la cantidad de memoria necesaria para contener la concatenación de s1 y s2 más el carácter \0 final.
	if (!joined)
		return (NULL);
	i = -1; // Se utiliza i = -1 y ++i para iniciar desde el índice 0 y avanzar correctamente por los caracteres.
	while (s1[++i])
		joined[i] = s1[i]; // La función copia todos los caracteres de s1 en la nueva cadena joined
	j = -1;
	while (s2[++j]) // Copia cada carácter de s2 directamente a joined en el mismo orden en que aparecen en s2
		joined[i++] = s2[j]; // igual solo que con s2
	joined[i] = '\0';
	free(s1);
	return (joined);
}
/**
 * @brief Searches for the first occurrence of a given character (c) 
 * in a string (s).
 * Returns a pointer to the found character, or NULL if not found.
 * 
 * @param s The string in which to search for the character.
 * @param c The character to search for in the string.
 * @return A pointer to the first occurrence of character c in string s,
 * or NULL if not found.
 */
int	ft_strchr(const char *s, int c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)s;
	if (!tmp)
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == (char)c)
			return (1);
		i++;
	}
	if ((char)c == '\0')
		return (0);
	return (0);
}
/**
 * @brief Calculates the length of a string
 * (excluding the null character).
 * 
 * @param str The string whose length is to be calculated.
 * @return The number of characters in the string.
 */
size_t	ft_strlen(const char *str)
{
	int	len;

	len  = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

