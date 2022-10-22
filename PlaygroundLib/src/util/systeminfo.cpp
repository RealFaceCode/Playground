#include "../../hdr/util/systeminfo.h"

#ifdef WIN64
#include <psapi.h>

const ui16 GetAmountProcessorCores()
{
    SYSTEM_INFO sInfo;
    GetSystemInfo(&sInfo);
    return (const ui16)sInfo.dwNumberOfProcessors;
}

const ProcessorArchitecture GetProcessorArchitecture()
{
    SYSTEM_INFO sInfo;
    GetSystemInfo(&sInfo);

    switch (sInfo.wProcessorArchitecture)
    {
        case PROCESSOR_ARCHITECTURE_UNKNOWN:
            return ProcessorArchitecture::UNKNOWN;
        case PROCESSOR_ARCHITECTURE_AMD64:
            return ProcessorArchitecture::X64_AMD_INTEL;
        case PROCESSOR_ARCHITECTURE_ARM:
            return ProcessorArchitecture::ARM;
        case PROCESSOR_ARCHITECTURE_ARM64:
            return ProcessorArchitecture::ARM64;
        case PROCESSOR_ARCHITECTURE_INTEL:
            return ProcessorArchitecture::X86;
        case PROCESSOR_ARCHITECTURE_IA64:
            return ProcessorArchitecture::INTEL_ITANIUM_BASED;
        default:
            return ProcessorArchitecture::UNKNOWN;
    }
}

const CPU_Info GetCPUInfo()
{
    return CPU_Info
    {
        .mProcessorCores         = GetAmountProcessorCores(),
        .mProcessorArchitecture  = GetProcessorArchitecture(),
        };
}

const RAM_Info GetRAMInfo()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

    return RAM_Info
    {
        .mVirtualMemory = {
                .mTotalVirtualMemInBytes            = memInfo.ullTotalPageFile,
                .mVirtualMemUsedInBytes             = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile,
                .mVirtualMemUsedByProgressInBytes   = pmc.PrivateUsage,
                .mTotalVirtualMemInKB               = (float)memInfo.ullTotalPageFile / 1024.f,
                .mVirtualMemUsedInKB                = (float)(memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / 1024.f,
                .mVirtualMemUsedByProgressInKB      = (float)pmc.PrivateUsage / 1024.f,
                .mTotalVirtualMemInMB               = (float)memInfo.ullTotalPageFile / (1024.f * 1024.f),
                .mVirtualMemUsedInMB                = (float)(memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / (1024.f * 1024.f),
                .mVirtualMemUsedByProgressInMB      = (float)pmc.PrivateUsage / (1024.f * 1024.f),
                .mTotalVirtualMemInGB               = (float)memInfo.ullTotalPageFile / (1024.f * 1024.f * 1024.f),
                .mVirtualMemUsedInGB                = (float)(memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / (1024.f * 1024.f * 1024.f),
                .mVirtualMemUsedByProgressInGB      = (float)pmc.PrivateUsage / (1024.f * 1024.f * 1024.f),
                },
                .mPhysicalMemory = {
                .mTotalPhysMemInBytes               = memInfo.ullTotalPhys,
                .mPhysMemUsedInBytes                = memInfo.ullTotalPhys - memInfo.ullAvailPhys,
                .mPhysMemUsedByProgressInBytes      = pmc.WorkingSetSize,
                .mTotalPhysMemInKB                  = (float)memInfo.ullTotalPhys / 1024.f,
                .mPhysMemUsedInKB                   = (float)(memInfo.ullTotalPhys - memInfo.ullAvailPhys) / 1024.f,
                .mPhysMemUsedByProgressInKB         = (float)pmc.WorkingSetSize / 1024.f,
                .mTotalPhysMemInMB                  = (float)memInfo.ullTotalPhys / (1024.f * 1024.f),
                .mPhysMemUsedInMB                   = (float)(memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024.f * 1024),
                .mPhysMemUsedByProgressInMB         = (float)pmc.WorkingSetSize / (1024.f * 1024.f),
                .mTotalPhysMemInGB                  = (float)memInfo.ullTotalPhys / (1024.f * 1024 * 1024.f),
                .mPhysMemUsedInGB                   = (float)(memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024.f * 1024.f * 1024.f),
                .mPhysMemUsedByProgressInGB         = (float)pmc.WorkingSetSize / (1024.f * 1024.f * 1024.f),
                .mMemoryLoadInPercent               = (const ui16)memInfo.dwMemoryLoad,
                },
    };
}

const System_Info GetSystemInfo()
{
    return System_Info{
        .mCPU_Info = GetCPUInfo(),
        .mRAM_Info = GetRAMInfo(),
        };
}

#endif