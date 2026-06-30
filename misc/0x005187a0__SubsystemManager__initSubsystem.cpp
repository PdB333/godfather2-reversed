// FUNC_NAME: SubsystemManager::initSubsystem
// Address: 0x005187a0
// Role: Initializes a subsystem using a count obtained from FUN_00518510 and two global data structures.
// Likely part of EA EARS engine initialization (e.g., memory pool or resource table setup).

#include <cstdint>

// Forward declarations for called functions (addresses known)
extern int32_t FUN_00518510(void);  // Returns some count or value
extern void FUN_005263c0(void* ptr1, void* ptr2, int32_t value); // Sets up data using ptr1, ptr2, and value

// Global data (pointers or identifiers)
extern void* _DAT_012192d8;  // +0x00: First global data/manager pointer
extern void* DAT_012192dc;   // +0x00: Second global data/count pointer

void FUN_005187a0(void)
{
    int32_t count = FUN_00518510();
    FUN_005263c0(_DAT_012192d8, DAT_012192dc, count);
    return;
}