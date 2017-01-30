#!/usr/bin/env python3
import subprocess
import sys

if not sys.argv[1]:
    print("No argument given!")
    sys.exit(1)

def extract_bootblock(bootobj, target):
    proc = subprocess.run(['objcopy', '-S', '-O', 'binary', '-j', '.text', '-j', '.rodata', bootobj, target])
    if proc.returncode:
        print("Error writing boot block")
        sys.exit(1)
    print("Boot block written to", target)

def pad_bootblock(bootblock):
    f = open(bootblock, "ab")
    if f.tell() > 510:
        print("File length can't be longer than 510")
        sys.exit(1)
    zero = bytes(b'\x00')
    magic = bytes(b'\x55\xAA')
    while f.tell() < 510:
        f.write(zero)
    f.write(magic)
    f.close()

extract_bootblock(sys.argv[2], sys.argv[1])
pad_bootblock(sys.argv[1])

sys.exit(0)
