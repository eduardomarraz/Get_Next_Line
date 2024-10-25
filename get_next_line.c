/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduamart <eduamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:54:45 by mnieto-m          #+#    #+#             */
/*   Updated: 2024/10/25 12:37:56 by eduamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/* El propósito de update_line es modificar la cadena str para que contenga solo el texto
   que aparece después de la primera línea (después del primer salto de línea \n).
   Si no hay más texto después del salto de línea, la función devuelve NULL. */
char	*update_line(char *str) // str -> Contiene el contenido leído
{
	int		i;
	int		j;
	char	*str_caract;	 // Esta cadena almacenará el texto que queda después de la primera línea, es decir, después del primer \n

	i = 0;
	while (str[i] != '\n' && str[i] != '\0') // Recorre str hasta encontrar (\n) o el final de la cadena (\0)
		i++;	// Al final del bucle será la posición del primer \n o el final de la cadena si no hay salto de línea.
	if (!str[i]) // Si str[i] es igual a '\0', significa que no se encontró un salto de línea, es decir, ya no hay más líneas para procesar.
	{
		free(str);	// Se libera la memoria ocupada por str porque ya no la necesitamos.
		return (NULL);
	}
	str_caract = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1)); // Se asigna memoria para a str_caract.
	if (!str_caract)
	{
		free (str); // Se libera la memoria ocupada por str porque ya no la necesitamos.
		return (NULL);
	}
	j = 0;
	i++;
	while (str[i]) // Mientras str[i] no sea '\0', se copian los caracteres de str a str_caract comenzando justo después del salto de línea.
		str_caract[j++] = str[i++]; // Se copia el carácter actual de str en str_caract, y se incrementan ambos índices para seguir copiando hasta llegar al final de str
	str_caract[j] = '\0'; // Se añade el carácter nulo ('\0') al final de str_caract para asegurarse de que es una cadena válida.
	free(str);
	return (str_caract); // Finalmente, se retorna la nueva cadena str_caract que contiene el texto después de la primera línea de str
}

/* El propósito de extract_line es extraer la primera línea de la cadena str
   y devolverla, incluyendo el salto de línea \n si está presente.
   Si no hay línea que extraer (cadena vacía o nula), la función retorna NULL. */
char	*extract_line(char *str) // str -> Contiene el contenido leído
{
	int		i;
	char	*line;

	i = 0;
	if (!str || str[0] == '\0') // Aquí se verifica si str es NULL o si tiene el primer carácter es '\0'.
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0') // Se recorre la cadena str carácter por carácter.
		i++;	// i termina siendo el número de caracteres antes del salto de línea o final de la cadena.
	line = (char *)malloc(sizeof(char) * (i + 2)); // Se asigna memoria para la cadena
			// i + 2 porque: -Se añade +1 para el salto de línea (\n) si existe.
						  // -Y otro +1 para el carácter nulo ('\0') que indica el final de la cadena.
	if (!line)
		return (NULL);
	i = 0;				// Se reinicia a 0
	while (str[i] != '\n' && str[i] != '\0') // Hace lo mismo de antes
	{
		line[i] = str[i];	//Copia la string a line
		++i;
	}
	if (str[i] == '\n')		// Se verifica si str[i] es un salto de línea (\n).
		line[i++] = '\n';	// Se copia el salto de línea a line y se incrementa i.
	line[i] = '\0';			// Se coloca carácter nulo al final de la cadena.
	return (line);
}

/* La función read_from_file lee datos desde un archivo asociado al descriptor fd
   y los almacena en la cadena str. Continúa leyendo hasta encontrar un salto de línea \n 
   o llegar al final del archivo. Si hay un error durante la lectura, retorna NULL. */
char	*read_from_file(int fd, char *str)
{
	int		bytes_read;
	char	*buffer; 	// Almacena temporalmente los datos leídos.

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); // Reservar memoria dinámica para un número de elementos, pero no inicializa la memoria
	if (!buffer)		// Gestion de Excepciones
		return (NULL);
	bytes_read = 1;
	while ((!ft_strchr(str, '\n')) && bytes_read != 0) // ft_strchr-> busca en la cadena str el carácter (\n). Si lo encuentra, el ciclo se detiene porque significa que ya tenemos una línea completa.
	// bytes_read != 0 -> Verifica que todavía hay datos por leer. read() devuelve 0 cuando llega al final del archivo.
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE); // read()-> lee hasta BUFFER_SIZE bytes desde el archivo fd y los almacena en el buffer. Retorna el número de bytes leídos.
		if (bytes_read < 0)		// Gestion de Excepciones
		{
			free(buffer);		// Se libera la memoria del buffer y de str para evitar fugas de memoria.
			free(str);
			return (NULL);
		}
		buffer[bytes_read] = '\0'; // Después de leer datos, el carácter nulo '\0' se coloca al final. Esto asegura que buffer sea una cadena de texto válida terminada en '\0'.
		str = ft_strjoin(str, buffer); // Combina la cadena acumulada en str con los nuevos datos leídos en buffer
	}
	free(buffer); // Libera la memoria del buffer, ya que no es necesaria.
	return (str); // Contiene lo que se ha leído del archivo hasta encontrar un salto de línea (o el final del archivo).
}

/* "fd -> El descriptor de archivo" es un número que el sistema operativo asigna cuando se abre un archivo (o un flujo de datos, como la entrada estándar).
 Este número actúa como una referencia para que el programa sepa a qué archivo o flujo de datos está accediendo al leer o escribir. */
char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0) // Gestion de Excepciones
		return (str = NULL);
	str = read_from_file(fd, str);
	if (!str)						// Gestion de Excepciones
		return (NULL);
	line = extract_line(str);
	str = update_line(str);
	return (line);
}
