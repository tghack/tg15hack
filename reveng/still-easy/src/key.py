key = [0xa, 0xb, 0xa, 0xd, 0xc, 0xa, 0xf, 0xe]
pw = "a~fySzn}ydxi"

cnt = 0
for c in pw:
   print(chr(ord(c) ^ key[cnt % len(key)]), end="")
   cnt += 1
print()
