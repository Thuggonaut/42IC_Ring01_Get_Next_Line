#include "gnl.h"

char	*get_next_line(int fd) //Define a function that takes in integer (a file descriptor), and returns a pointer to a character
{
	char	buffer[10960]; //Declare a character array that will be used to store the characters read from a file. `10960` size to make it big enough for Moulinnette to read
	char	*line; //Declare a pointer variable that will point to a character, and will be used to store the line read from a file
	ssize_t	bytes_read; //Declare a `ssize_t` variable that will be used to keep track of the number of bytes read from the file

	bytes_read = 0; //Initialised to `0` as no bytes have been read yet
	if (fd == -1 || read(fd, &buffer[0], 0) == -1 || BUFFER_SIZE == 0) //Check if `fd` is `-1`, implying an error and the file can't be opened; if reading from the `fd` fails; or if `BUFFER_SIZE` is `0`. See #1
		return (NULL); //If any is true, return `NULL`
	while (read(fd, &buffer[bytes_read], 1) > 0 && buffer[bytes_read++] != '\n') //Read from the file one character at a time and check if the character read is a newline character ('\n'). See #2
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
#1  `if (fd == -1 || read(fd, &buffer[0], 0) == -1 || BUFFER_SIZE == 0)`:
	- is a conditional statement that checks for three possible error conditions before the function proceeds to read from the file. If any are true, the 
	  function immediately returns `NULL`:

	1. `fd == -1`: 
		- This checks if the file descriptor `fd` is `-1`. 
		- In Unix-like operating systems, `-1` is often used as the return value of a function that fails to open a file. 
		- So, if `fd` is `-1`, it means that the file failed to open.

	2. `read(fd, &buffer[0], 0) == -1`: 
		- This is a bit tricky. The `read` function is being called with a count of `0`, which means it doesn't actually read any data. 
		- Instead, this call to read is used as a way to check if `fd` is a valid file descriptor that can be read from. 
		- If `fd` is not valid, `read()` will return `-1`. 
		- So, if `read(fd, &buffer[0], 0) == -1`, it means that `fd` is not a valid file descriptor.

	3. `BUFFER_SIZE == 0`: 
		- This checks if `BUFFER_SIZE` is `0`. 
		- `BUFFER_SIZE` is a macro that specifies the size of the buffer used to read data from the file. 
		- If `BUFFER_SIZE` is `0`, it means that the buffer size is not properly set, and thus the function cannot proceed to read from the file.


#2	`while (read(fd, &buffer[bytes_read], 1) > 0 && buffer[bytes_read++] != '\n')	;`:
	- this while loop reads characters from the file one at a time into the buffer until it encounters a newline character or reaches the end of the file. 
	  The number of characters read (not including the newline character) is stored in `bytes_read`.

	1. `read(fd, &buffer[bytes_read], 1) > 0`: 
		- The `read` function is called to read one character from the file descriptor `fd` and store it in the buffer at the position indicated by 
		  `bytes_read`. 
		- The `read` function returns the number of bytes read, or `-1` if an error occurred. 
		- So, `read(fd, &buffer[bytes_read], 1) > 0` checks if at least one byte was read, which means that the end of the file has not been reached.

	2. `buffer[bytes_read++] != '\n'`: 
		- This checks if the character just read is not a newline character ('\n'). 
		- The `bytes_read++` part is a post-increment operation, which means that `bytes_read` is incremented after its value is used. 
		- So, `buffer[bytes_read++]` gets the character just read, and `bytes_read` is then incremented to prepare for the next read operation.

	3. `while (read(fd, &buffer[bytes_read], 1) > 0 && buffer[bytes_read++] != '\n') ;`: 
		- The while loop continues as long as both conditions are true: that is, as long as 
			- there are more characters to read from the file, and 
			- the character just read is not a newline character. 
		- When a newline character is encountered, the loop breaks, and the function proceeds to the next line of code.

	4. The semicolon (;) at the end of the line indicates that this while loop has no body. 
		- This is known as a "do nothing" or "null" statement. 
		- It means that the loop continues to iterate, reading one character at a time from the file, but doesn't perform any other action within the loop. 
		- The work is done in the condition itself: reading from the file and checking for the newline character.
*/
