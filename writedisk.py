#!/usr/bin/env python3
import sys
import subprocess
import struct

def write_stage2(drive, stage2):
    proc = subprocess.run(['wc', '-c', stage2], stdout=subprocess.PIPE)
    size = int(str(proc.stdout, 'utf8').split()[0])
    with open(drive, 'ab') as f1, open(stage2, 'rb') as f2:
        f1.write(struct.pack("I", size))
        f1.write(f2.read())

write_stage2(sys.argv[1], sys.argv[3])

sys.exit(0)
