#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <TlHelp32.h>

int main(int argc, char *argv[])
{
    PROCESSENTRY32 ProcessEntry={0};
    ProcessEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE Snapshot32Process = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);

    if(Snapshot32Process==INVALID_HANDLE_VALUE)
        exit(EXIT_FAILURE);

    if(!Process32First(Snapshot32Process, &ProcessEntry)) {
            CloseHandle(Snapshot32Process);
            exit(EXIT_FAILURE);
    }

    printf("%8s %6c %8s %32s\n\n", "PPID", '-', "PID", "Process Name");
    while (Process32Next(Snapshot32Process, &ProcessEntry)){
            printf("%8d %6c %8d %32s\n", ProcessEntry.th32ParentProcessID, '-', ProcessEntry.th32ProcessID, ProcessEntry.szExeFile);
    }

    CloseHandle(Snapshot32Process);
    return 0;
}
