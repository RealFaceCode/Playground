#ifndef PLAYGROUNDLIB_SYSTEMINFO_H
#define PLAYGROUNDLIB_SYSTEMINFO_H

#include "../core.h"

/**@brief Defines with architectures are supported*/
enum class ProcessorArchitecture
{
    UNKNOWN             = 0,
    X64_AMD_INTEL       = 1,
    ARM                 = 2,
    ARM64               = 3,
    X86                 = 4,
    INTEL_ITANIUM_BASED = 5,
};

/**@brief Holds the information about how many processor core the cpu has and witch architecture it has*/
struct CPU_Info
{
    const ui16                  mProcessorCores;
    const ProcessorArchitecture mProcessorArchitecture;
};

/**@brief Holds the information about the physical and the virtual memory*/
struct RAM_Info
{
    /**@brief holds the information about the virtual memory*/
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

    /**@brief Holds the information of the physical memory*/
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

/**@brief Holds the information over the memory and the cpu*/
struct System_Info
{
    CPU_Info mCPU_Info;
    RAM_Info mRAM_Info;
};

/**@brief Gets the amount of processor cores the cpu has
 * @returns
 * Returns the amount of processor cores the cpu has without virtual cores
 */
const ui16 GetAmountProcessorCores();
/**@brief Gets the architecture of the cpu
 * @retval UNKNOWN
 * @retval X64_AMD_INTEL
 * @retval ARM
 * @retval ARM64
 * @retval X86
 * @retval INTEL_ITANIUM_BASED
 */
const ProcessorArchitecture GetProcessorArchitecture();
/**@brief Gets the cpu information
 * @returns
 * Returns the information of the cpu as a struct
 */
const CPU_Info GetCPUInfo();
/**@brief Gets the memory information
 * @returns
 * Returns the information of the memory as a struct
 */
const RAM_Info GetRAMInfo();
/**@brief Gets the system information
 * @returns
 * Returns the information of the system as a struct
 */
const System_Info GetSystemInfo();

#endif //PLAYGROUNDLIB_SYSTEMINFO_H
