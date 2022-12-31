# utilities-hex2bits
hexadecimal to bits  converter (command line tool)

- Reads hex from command line input (0xff 0xef5c ...) or from file passed in argument.
- Display format 16/32+ bits

```
Usage: ./hex2bits 0x... or ./hex2bits file
./hex2bits 0xff 0x3c3d 0xff35
./hex2bits list.txt

      Bits            Bit    Hex
0000 0000 0000 0001   1.00  (0x1)
0000 0000 0000 0010   1.58  (0x2)
0000 0000 0000 0100   2.32  (0x4)
0000 0000 0000 1000   3.17  (0x8)
0000 0000 0001 0000   4.09  (0x10)
0000 0000 0010 0000   5.04  (0x20)
0000 0000 0100 0000   6.02  (0x40)
0000 0000 1000 0000   7.01  (0x80)
0000 0001 0000 0000   8.01  (0x100)
0000 0100 0000 0000  10.00  (0x400)
0001 0000 0000 0000  12.00  (0x1000)
0100 0000 0000 0000  14.00  (0x4000)
      Bits                            Bit    Hex
00010000 11000011 11111111 00100101  28.07  (0x10c3ff25)
00011111 10000110 11111100 11011111  28.98  (0x1f86fcdf)
00011101 10011100 11111010 10011100  28.89  (0x1d9cfa9c)
```
