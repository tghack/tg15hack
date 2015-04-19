# IBM (150 points)

The newest crypto technology from IBM. Can you find the token? `10.20.230.30` port `1337`.

(I've added a file containing the output from the server [here](output).)

## How to solve
1. `nc <host> <port>  > ibm`
2. `file ibm` gives: `ibm: Non-ISO extended-ASCII text, with NEL line terminators`
3. Googling `NEL line terminator` takes us to Wikipedia, which tells us that EBCDIC systems use NEL line terminators.
4. dd to the rescue! `dd conv=ascii if=ibm of=ibm_out`
5. `cat ibm_out`
`Security through obsurity ftw! Token: EBCDIC=encryption`
