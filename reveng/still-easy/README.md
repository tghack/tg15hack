# Still easy? (200 points)

### Write-up

This binary is a little harder than the first two, as it doesn't use standard library functions to compare the passwords.

Trying to trace it also gives us the following message:
```
$ ltrace ./easy3
__libc_start_main(0x400980, 1, 0x7fffffffe918, 0x400a60 <unfinished ...>
ptrace(0, 0, 1, 0)                                                       = -1
puts("no trace pls :("no trace pls :(
)                                                  = 16
exit(1 <no return ...>
+++ exited (status 1) +++
```

Which means that the program uses a ptrace trick to avoid debuggers attaching to the process.
We could simply remove this check, or force the program to continue execution instead of exiting, but because the main function isn't obfuscated, let's use some good old static analysis.

We can decompile the function by hand, and it looks something like this:

```C
fwrite(stdout, "Password: ", 10);

int len = read(stdin, buf, 0x31); /* 0x31 = 49 */
buf[len - 1] = '\0';

/* this encrypts the input password */
xor_encrypt(buf, key);

if (_strcmp(pw, buf)) {
	success!
} else {
	fail!
}

```

The entered password is XOR-ed with a key, and then compared with the XOR-encrypted password.
Using (for example) `radare2`, we can print out these values:

```
[0x00400690]> ps @ sym.pw
a~fySzn}ydxi
[0x00400690]> px @ sym.key
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x00600f68  0a0b 0a0d 0c0a 0f0e 617e 6679 537a 6e7d  ........a~fySzn}
[...]
```

If you look closely, the key and the encrypted password lie right next to each other in memory, so 0x0e is the
last value of the key.

Let's use python!

```python
key = [0xa, 0xb, 0xa, 0xd, 0xc, 0xa, 0xf, 0xe]
pw = "a~fySzn}ydxi"

cnt = 0
for c in pw:
   print(chr(ord(c) ^ key[cnt % len(key)]), end="")
   cnt += 1
print()
```

```
$ python key.py
kult_passord
$ ./easy3      
Password: kult_passord
Correct! Token is: verySecret
```
