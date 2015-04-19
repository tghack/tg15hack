# Secrets

**Points: 750**


### Writeup

**TODO**: Better text and some pretty pictures.

1. Skip the IsDebuggerPresent jump
2. OutputDebugString? No thanks.
3. Break on `call ebx`
4. Copy the decrypted blob and view it in something nice (like radare2)

Okay, now we have something to work with. A giant blob of assembly...
This function is massive, probably because everything has been inlined.
As we do not want to decompile 195 lines of assembly by hand, let's try and find something interesting.

After looking angrily at the code for some time, we see that the blob has two exit points: one at offset 0x242 and one at 0x29f.
Which one is the correct one? We can either run the program, type in a random password, and see which path it takes, or assume that the one at 0x29f is the `bad boy` message. The one at 0x242 looks correct because it has several calls to `[esp + 0x840]`, which olly kindly tells us is the `_write` function.

The most straight forward way of solving this now NOP-ing out all the jumps to 0x243 and greater.
After NOP-ing out all the jumps we can sit back and let the horrible function decrypt the token for us.
