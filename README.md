*This project has been created as part of the 42 curriculum by relyaman.*

# get_next_line

## Description

`get_next_line` is a C function that returns **one line at a time** from a file descriptor, including the trailing `\n` when there is one. It returns `NULL` at the end of the file or on error.

```c
char *get_next_line(int fd);
```

The goal is to learn about static variables, file descriptors, `read()`, and dynamic memory management. It works with any `BUFFER_SIZE` set at compile time.

**Bonus:** the bonus version uses a single static array and can read from several file descriptors at the same time without mixing their data.

## Instructions

Mandatory:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```

Bonus:

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

Use -D BUFFER_SIZE=number to change buffer size .
like

Example:

```c
int fd = open("test.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)))
{
	printf("%s", line);
	free(line);
}
close(fd);
```

## Algorithm

`read()` returns a fixed number of bytes, not a line, so it may return half a line or several lines. The data read beyond the current line must be kept for the next call.

I use a **static stash** (`static char *st`) that stores what has been read but not yet returned. Each call does three steps:

1. **`read_and_next`**: read chunks of `BUFFER_SIZE` and append them to the stash until it contains a `\n` or the end of the file is reached.
2. **`extract_line`**: copy the stash up to and including the first `\n` into a new string, which is returned.
3. **`clean_next`**: keep only what comes after the `\n` as the new stash, or free it if nothing is left.

This works for any `BUFFER_SIZE`, loses no data between calls, and keeps each function small and simple (Norm-friendly). Every allocation is freed on all paths, so there are no leaks.

For the bonus, the stash becomes `static char *st[FD]`, giving each file descriptor its own independent stash.

## Resources

- [`man 2 read`](https://man7.org/linux/man-pages/man2/read.2.html)

**Use of AI:** I used Claude to help me understand Some things algorithm the user has to do get_next_line and to know about file descriptor 
