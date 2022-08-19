//
// Created by Kevin-Laptop on 19.08.2022.
//

#include "../hdr/mempicker.h"

#ifdef WIN32
#include "tlhelp32.h"
HANDLE GetProcessByName(PCSTR name)
{
    DWORD pid = 0;

    // Create toolhelp snapshot.
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    // Walkthrough all processes.
    if (Process32First(snapshot, &process))
    {
        do
        {
            // Compare process.szExeFile based on format of name, i.e., trim file path
            // trim .exe if necessary, etc.
            if (std::string(process.szExeFile) == std::string(name))
            {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);

    if (pid != 0)
    {
        return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    }

    // Not found
    return NULL;
}

HMODULE GetModule(HANDLE handle)
{
    HMODULE hMods[1024];
    HANDLE pHandle = handle;
    DWORD cbNeeded;
    unsigned int i;

    if (EnumProcessModules(pHandle, hMods, sizeof(hMods), &cbNeeded))
    {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            char  szModName[MAX_PATH];
            if (GetModuleFileNameEx(pHandle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
            {
                std::string wstrModName(szModName);
                //you will need to change this to the name of the exe of the foreign process
                std::string wstrModContain = "Sandbox.exe";
                if (wstrModName.find(wstrModContain) != std::string::npos)
                {
                    CloseHandle(pHandle);
                    return hMods[i];
                }
            }
        }
    }
    return nullptr;
}
#endif