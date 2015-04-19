# easy2 (150 points)

### Write-up

This one is a little harder, since there are no obvious strings in the binary.
Using tools like `strings`, `nm`, etc. we can easily see that the binary is using `strcmp`. Maybe it's using it to check the password?

Luckily, we have the fantastic `ltrace` tool. This tool traces all the dynamic library calls of a program.

```shell
$ ltrace ./easy2
__libc_start_main(0x4006a6, 1, 0x7fffffffe918, 0x4007a0 <unfinished ...>
fwrite("Password: ", 1, 10, 0x7ffff7dd6640Password: )                              = 10
read(0foo
, "foo\n", 49)                                                     = 4
strcmp("foo", "TG15")                                                    = 18
printf("Wrong password!")                                                = 15
putchar(10, 33, 0x7ffff7dd7970, 1024Wrong password!
)                                    = 10
+++ exited (status 0) +++
```

Wasn't that easy? As we can see from the ltrace output, our input (`foo`) is compared with `TG15`. Hmmm... Maybe this is the password?

```shell
$ ./easy2 
Password: TG15
Correct! The token is: 4iqvMHSH(0
```
