#!/usr/bin/env python3
import sys
import subprocess
import struct

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

def write_stage2(drive, stage2):
    proc = subprocess.run(['wc', '-c', stage2], stdout=subprocess.PIPE)
    size = int(str(proc.stdout, 'utf8').split()[0])
    with open(drive, 'ab') as f1, open(stage2, 'rb') as f2:
        f1.write(struct.pack("I", size))
        f1.write(f2.read())

extract_bootblock(sys.argv[2], sys.argv[1])
pad_bootblock(sys.argv[1])
write_stage2(sys.argv[1], sys.argv[3])

sys.exit(0)
