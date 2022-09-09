## Reverse Shell Explained

**Description**<br />
The idea behind the reverse shell is to first create a socket connection with the attackers machine. To do this we use `winsock2.h` to create a socket, and connect that socket to the attacker's IP and port. The second step in creating the reverse shell is to pipe all the standard input, standard output, and standard error of the victim's machine to the socket connected to the attacker's machine. The final step is to spawn `cmd.exe` with `CreateProcess` and tell the process to not terminate.

