//
// Created by Kevin-Laptop on 19.08.2022.
//

#ifndef PLAYGROUNDLIB_MEMPICKER_H
#define PLAYGROUNDLIB_MEMPICKER_H

#ifdef WIN32
#include <windows.h>
#include <psapi.h>

HANDLE GetProcessByName(PCSTR name);
HMODULE GetModule(HANDLE handle);
#endif

#endif //PLAYGROUNDLIB_MEMPICKER_H
