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
1. FILE type
2. errno
3. perror
4. fread
5. fopen
6. fclose
7. rwrite
8. strncpy
