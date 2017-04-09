settings set plugin.process.gdb-remote.target-definition-file /home/pwarner/.lldb/x86_64_target_definition.py
script
import subprocess

proc = subprocess.Popen(['qemu-system-x86_64', '-cdrom', 'os.iso', '-s', '-S'])

listener = lldb.debugger.GetListener()
error = lldb.SBError()
target = lldb.debugger.CreateTargetWithFileAndArch('src/kern/kernel', 'x86_64')
lldb.debugger.HandleCommand("gdb-remote 1234")

lldb.debugger.HandleCommand("breakpoint set --name main")
lldb.debugger.HandleCommand("continue")

exit()