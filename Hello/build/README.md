- ex7: reveiew on variables and typs
- ex10: swtich statements
- ex17: database execution


## Deep dive into Switch Statements
- In Ruby, `switch-statement` can take any expressions.
- Some language like Python, do not have a `switch-statement` because an `if-statement` with Boolean expressions is about the same thing.
- In C, the `switch-statement` is actually quite different
- It is a jump table.
- Instead of random Boolean expressions, you can only put expressions that result in integers.
- These int are used to calculate jumps from the top of the `switch` to the part that matches that value.

### Breaking it down
1. The compiler aranges places `Y` for `switch-statement`.
2. It evaluates the expression in `switch` and come up with a number. In this case, the number will be the raw ASCII code of the letter in argv[1].
3. The compiler also translates each of the `case` block in the program distance away from `switch`. For instance, `case 'A'` is at `Y+A` in the program.
4. It then does the math to figure out where `Y` + `letter` is locates in the statement. If the location is too far, the program adjusts location to `Y` + `default`.
5. Once the program determines the location, the program jumps to that spot in the code, and continues running. That is the reason we have to add break on some of the case blocks and some not.

## How to read an array
```
int areas[] = {1,2,3};
char name[] = "Megan";
```
- I want an array named `areas` of type `int` that is initialized to `1,2,3`.
- I want another array named `name` of type `char` that is initialized to `M, e, g, a, n`.


## Functions lookup
> file handling in C is a process where we create, open, read, write and close operations on a file. C language provides different functions such as fopen, fwrite, fread, fseek, fprintf, etc. to perform input, output, and many different C file operations in the program.
> files can be classified into two types - text files, binary files.
> A text file contains data in the form of ASCII characters and is generally used to store a stream of characters. Each line in a text file ends with a new line character `\n`.
> A binary file contains data in binary form. The file contain data that is stored in a similar way to how it is stored in the main memory.
### C File operations
- Create a new file : `fopen` with attrs as 'a', 'a+', 'w', 'w+', ...
- Open an existing file : `fopen`
- Read from file : `fscanf`, `fgets`
- Write to file : `fprintf`, `fputs`
- Move to a specific location : `fseek`, `rewind`
- Close a file : `fclose`

1. FILE type
> A file pointer is a reference to a particular position in the opened file. It is used in file handling to perform all file operations such as read, write, close, etc. We use **FILE** macro to declare the file pointer variable. The **FILE** macro is defined in `<stdio.h>` header file.
2. errno
3. perror
4. fread
5. fopen
> For opening a file in C, the function is used with the filename or filepath along with the required access modes.
> If the file is opened successfully, the function returns a file pointer. else returns NULL. -> If the file opened successfully, `fopen` loads it into memory, and sets up a pointer that points to the first character in it.
`FILE* fopen(const char *file_name, const char *access_mode);`
**Opening modes:** 
6. fclose
7. rwrite
8. strncpy
