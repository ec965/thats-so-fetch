# Fetch
# Header Files for C
- `<sys/utsname.h>`
    * [manpages](https://www.man7.org/linux/man-pages/man2/uname.2.html)
    * OS
    * Node/hostname
    * Kernel
    * machine
- [`<sys/sysinfo.h>`](https://stackoverflow.com/questions/1540627/what-api-do-i-call-to-get-the-system-uptime)
    * [manpages](https://man7.org/linux/man-pages/man2/sysinfo.2.html)
    * uptime
    * memory
- `<unistd.h>`
    * [manpages](https://linux.die.net/man/3/getlogin_r)
    * username

# Files
- `/etc/os-release`
    * OS
- `/proc/sys/kernel`
    * Host Name
- `/proc/sys/ostype /proc/sys/osrelease`
    * Kernel
- `/proc/cpuinfo`
    * CPU

# System commands (bash)
[Run system commands in C with system().](https://stackoverflow.com/questions/5237482/how-do-i-execute-external-program-within-c-code-in-linux-with-arguments)
- `lshw -C display`
    * GPU
- `cat /etc/alternatives/x-terminal-emulator | grep exec`
    * terminal emulator
- `$SHELL --version`
    * shell

# Enviromental Variables
Enviromental variables can also be called in C with [`envp`](https://www.geeksforgeeks.org/c-program-print-environment-variables/).

- `$XDG_CURRENT_DESKTOP`
    * Desktop environment
- `$LANG`
    * language

# Colors
Colors can be output in the terminal with [ANSI escape codes](https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c).
