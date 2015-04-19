# easy1 (100 points)

Can you find the hidden token?

Download [here](easy1).

### Write-up

There are many ways to solve this challenge, as there are no protections at all hiding the password or the token.

One way is to use `strings` and look for something interesting.

```shell
strings easy1
/lib64/ld-linux-x86-64.so.2
libc.so.6
[...]
secret
F62wAk-aY3<PCoF
[...]
_ITM_registerTMCloneTable
_init
stderr@@GLIBC_2.2.5
```

At the top we can see the following strings, `secret` is probably the password, and `F62wAk-aY3<PCoF` is probably the token. Let's check.

```shell
$ ./easy1 
Enter the secret password: secret
Correct! The token is: F62wAk-aY3<PCoF
```
