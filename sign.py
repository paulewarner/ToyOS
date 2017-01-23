#!/usr/bin/env python3
import sys

if not sys.argv[1]:
    print("No argument given!")
    sys.exit(1)

f = open(sys.argv[1], "ab")
if f.tell() > 510:
    print("File length can't be longer than 510")
    sys.exit(1)

zero = bytes(b'\x00')
magic = bytes(b'\x55\xAA')

while f.tell() < 510:
    f.write(zero)

f.write(magic)

f.close()

sys.exit(0)
