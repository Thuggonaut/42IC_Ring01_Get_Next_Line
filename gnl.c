#include "gnl.h"

char	*get_next_line(int fd) //Define a function that takes in integer (a file descriptor), and returns a pointer to a character
{
	char	buffer[10960]; //Declare a character array that will be used to store the characters read from a file. `10960` size to make it big enough for Moulinnette to read
	char	*line; //Declare a pointer variable that will point to a character, and will be used to store the line read from a file
	ssize_t	bytes_read; //Declare a `ssize_t` variable that will be used to keep track of the number of bytes read from the file

	bytes_read = 0; //Initialised to `0` as no bytes have been read yet
	if (fd == -1 || read(fd, &buffer[0], 0) == -1 || BUFFER_SIZE == 0) //Check if `fd` is `-1`, implying an error and the file can't be opened; if reading from the `fd` fails; or if `BUFFER_SIZE` is `0`. See #1
		return (NULL); //If any is true, return `NULL`
	while (read(fd, &buffer[bytes_read], 1) > 0 && buffer[bytes_read++] != '\n') //
		;
	if (bytes_read == 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (bytes_read + 1));
	if (!line)
		return (NULL);
	line[bytes_read] = '\0';
	while (--bytes_read > -1)
	{
		line[bytes_read] = buffer[bytes_read];
	}
	return (line);
}

/*
#1  
*/
