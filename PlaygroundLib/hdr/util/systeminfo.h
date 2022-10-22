#ifndef PLAYGROUNDLIB_SYSTEMINFO_H
#define PLAYGROUNDLIB_SYSTEMINFO_H

#include "../core.h"

enum class ProcessorArchitecture
{
    UNKNOWN             = 0,
    X64_AMD_INTEL       = 1,
    ARM                 = 2,
    ARM64               = 3,
    X86                 = 4,
    INTEL_ITANIUM_BASED = 5,
};

struct CPU_Info
{
    const ui16                  mProcessorCores;
    const ProcessorArchitecture mProcessorArchitecture;
};

struct RAM_Info
{
    struct VirtualMemory
    {
        const ui64  mTotalVirtualMemInBytes;
        const ui64  mVirtualMemUsedInBytes;
        const ui64  mVirtualMemUsedByProgressInBytes;
        const f64   mTotalVirtualMemInKB;
        const f64   mVirtualMemUsedInKB;
        const f64   mVirtualMemUsedByProgressInKB;
        const f64   mTotalVirtualMemInMB;
        const f64   mVirtualMemUsedInMB;
        const f64   mVirtualMemUsedByProgressInMB;
        const f64   mTotalVirtualMemInGB;
        const f64   mVirtualMemUsedInGB;
        const f64   mVirtualMemUsedByProgressInGB;
    };

    struct PhysicalMemory
    {
        const ui64  mTotalPhysMemInBytes;
        const ui64  mPhysMemUsedInBytes;
        const ui64  mPhysMemUsedByProgressInBytes;
        const f64   mTotalPhysMemInKB;
        const f64   mPhysMemUsedInKB;
        const f64   mPhysMemUsedByProgressInKB;
        const f64   mTotalPhysMemInMB;
        const f64   mPhysMemUsedInMB;
        const f64   mPhysMemUsedByProgressInMB;
        const f64   mTotalPhysMemInGB;
        const f64   mPhysMemUsedInGB;
        const f64   mPhysMemUsedByProgressInGB;
        const ui16  mMemoryLoadInPercent;
    };

    VirtualMemory   mVirtualMemory;
    PhysicalMemory  mPhysicalMemory;
};

struct System_Info
{
    CPU_Info mCPU_Info;
    RAM_Info mRAM_Info;
};

const ui16 GetAmountProcessorCores();
const ProcessorArchitecture GetProcessorArchitecture();
const CPU_Info GetCPUInfo();
const RAM_Info GetRAMInfo();
const System_Info GetSystemInfo();

#endif //PLAYGROUNDLIB_SYSTEMINFO_H
