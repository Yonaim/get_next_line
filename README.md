# get_next_line

`get_next_line` is a personal implementation of a function that reads lines from a file descriptor (fd) line by line. It was designed as a study project to improve understanding of file I/O operations, memory management, and static variables in C.

This repository includes two different implementations:

- **Single File Descriptor (`single_fd`):**
  Handles input from a single file descriptor.

- **Multiple File Descriptors (`multi_fd`):**
  Capable of handling input from multiple file descriptors simultaneously, maintaining separate states for each fd.

## Project Purpose

- Enhance knowledge of dynamic memory allocation and static variables.
- Understand file descriptors and file I/O management in Unix-like systems.
- Practice robust error-handling and buffer management techniques.

## Function Prototype

```c
int get_next_line(int fd, char **line);
```

## Usage

Include the `get_next_line.h` or `get_next_line_multiple.h` header in your project:

```c
#include "get_next_line.h"
```

```c
#include "get_next_line_multiple.h"
```

Compile your code with the desired implementation (single or multiple fd):

### Single File Descriptor

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 single_fd/get_next_line.c single_fd/get_next_line_utils.c yourfile.c -I single_fd
```

### Multiple File Descriptors

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 multi_fd/get_next_line.c multi_fd/get_next_line_utils.c yourfile.c -I multi_fd
```

You can adjust `BUFFER_SIZE` as needed.

## Example

Here's a simple usage example:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        printf("%s\n", line);
        free(line);
    }
    free(line);
    close(fd);
    return 0;
}
```

## Directory Structure

```
get_next_line
├── single_fd
│   ├── get_next_line.c
│   ├── get_next_line_utils.c
│   └── get_next_line.h
└── multi_fd
    ├── get_next_line.c
    ├── get_next_line_utils.c
    └── get_next_line.h
```
