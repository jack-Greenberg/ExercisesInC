#include <stdio.h>

int main() {
    int x = 5;
    int y = x + 1;

    printf("%d", y);
    return 0;
}

/* Optimization
1. The only additional code is
```
subq	$16, %rsp
movl	$5, -4(%rbp)
```
and instead of `popq    %rbp`, I see `leave` in the version with x = 5.

2. Adding -O2 causes the assembly code file to be shorter and removes some of the instructions.
It shortens the .LFB0 section, and changes its name to .LFB23

3. Printing x adds
```
movl	-4(%rbp), %eax
movl	%eax, %esi
```
and changes the .string at the top from "Hello, World" to "%d". In the optimized assembly language
the only addition is `movl	$5, %edx`.

4. The unoptimized code adds 5 additional lines to the version where we printed x, but
the optimized code only changes a single line, and the line `movl    $5, -4(%rbp)` changes the 5 to a 6.

5. Optimization looks at the final results of variables and only includes information about
their final state as needed by other functions. If we were to print both x and y, there
would probably be additional information about in the optimized version.

*/
