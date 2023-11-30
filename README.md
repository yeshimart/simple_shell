# Simple Shell

This is a project for Holberton School that aims to create a simple UNIX command line interpreter or shell. The shell is capable of reading commands from the user both in interactive and non-interactive mode and executing them.

## Requirements

- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to
- Write a README with the description of your project
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

## Installation and Usage

To compile the shell, use the following command:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

To run the shell in interactive mode, use the command:

```
./hsh
```

To run the shell in non-interactive mode, use the command:

```
echo "command" | ./hsh
```

Replace "command" with the desired command to execute.

## Features

- Reads commands from the user
- Executes commands with arguments
- Handles built-in commands (e.g., `cd`, `exit`)
- Handles PATH resolution for commands
- Supports input/output redirection (`>`, `<`)
- Supports piping of commands (`|`)

## Examples

Interactive mode:

```
$ ./hsh
($) /bin/ls
file1 file2 file3
($) cd directory
($) /bin/pwd
/home/user/directory
($) exit
```

Non-interactive mode:

```
$ echo "/bin/ls" | ./hsh
file1 file2 file3
```
**By `YESHITLA TEGAW`**
