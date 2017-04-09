import subprocess
import os
def my_ignore_errors(arg):
    try:
        gdb.execute(arg)
    except:
        pass
gdb.execute("symbol-file {}".format(os.path.join(os.getcwd(), 'src', 'kern', 'kernel')))
proc = subprocess.Popen(['qemu-system-x86_64', '-cdrom', 'os.iso', '-s', '-S'])
gdb.execute("target remote localhost:1234")
gdb.execute("break main")
my_ignore_errors("continue")
gdb.execute("disconnect")
gdb.execute('set architecture i386:x86-64')
gdb.execute("target remote localhost:1234")
