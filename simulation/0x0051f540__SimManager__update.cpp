// FUNC_NAME: SimManager::update
// Function address: 0x0051f540
// EARS engine main game sim update loop. Manages linked list of sim objects, slot-based focus, and timing.

#include <windows.h> // For LARGE_INTEGER, QueryPerformanceCounter

// Forward declarations of called functions
extern void FUN_0051fc90(bool resetFlag); // maybe updateObject
extern void FUN_0051fc40(); // maybe processObject
extern void FUN_0051ead0(); // maybe cleanup
extern int FUN_005246b0(); // maybe getCurrentTime
extern void FUN_0042ed50(int, int); // maybe some setter

// Global static members of SimManager (or global variables)
static int g_focusSlot;                    // DAT_011f38f8 - current focus slot index
static int g_activeSlotCount;              // DAT_011f38fc - number of active slots?
static int g_slotOwners[20];               // DAT_01218e50 - array mapping slot index to object ID (0x14 entries)
static int g_slotFlags[20];                // DAT_01218e54 - flags per slot (bitfield)
static void* g_engine;                     // DAT_01205750 - pointer to Engine singleton (vtable at +0)
static void* g_objectPoolBase;             // DAT_011a0f28 - base of object pool (each entry 0x38 bytes)
static int g_someConst;                    // DAT_00f158f0 - some constant passed to vcall

// Timing globals
static LARGE_INTEGER g_lastTime;           // DAT_01194b78 - low part, DAT_01194b7c - high part
static LARGE_INTEGER g_deltaTime;          // DAT_01194b70 - low part, DAT_01194b74 - high part

// Flags
static char g_updateFlag;                  // DAT_01163cf5 - set to 1 after reset
static char g_cleanupFlag;                 // DAT_01163cf6 - triggers cleanup call
static char g_pauseFlag;                   // DAT_012054eb - if set, skip certain processing

void SimManager::update(bool resetFlag)
{
    int* piVar1;
    int iVar3;
    uint uVar2;
    uint uVar4;
    int iVar6;
    bool bVar7;
    LARGE_INTEGER localTime;

    uVar4 = g_focusSlot;
    g_cleanupFlag = 0;

    uVar2 = 0;
    if (resetFlag) {
        // Reset all slots: find first slot with owner == 0 and clear its flags
        uVar2 = 0;
        do {
            if (g_slotOwners[uVar2] == 0) {
                if (uVar2 < 20) {
                    g_slotFlags[uVar2] &= 0xfffffffc; // clear bits 0-1
                }
                break;
            }
            uVar2 = uVar2 + 1;
        } while (uVar2 < 20);

        iVar6 = g_activeSlotCount;
        bVar7 = (g_focusSlot != 0);
        g_focusSlot = 0;
        g_activeSlotCount = 0;
        uVar2 = uVar4;
        if (bVar7 || (iVar6 != 0)) {
            // Call engine method at vtable+0x94 (likely something like setActiveSlot or reset)
            (**(code**)(*(int*)g_engine + 0x94))(g_engine, 1, 0);
        }
    }

    // Record start time of this update
    QueryPerformanceCounter(&localTime);
    g_lastTime = localTime; // store low and high

    if (resetFlag) {
        g_deltaTime.u.LowPart = 0;
        g_deltaTime.u.HighPart = 0;
        g_updateFlag = 1;

        if (g_pauseFlag == 0) {
            // Reset some counters and iterate through internal list
            // These might be class members: this+4 is list head, this+0xc is list tail
            // Offsets +0x14 and +0x1c might be some counters per object
            int* headPtr = *(int**)(this + 4);
            int* tailPtr = *(int**)(this + 0xc);
            // This loop looks for an object whose internal counter at +0x14 matches counter at +0x1c
            // It calls FUN_005246b0() repeatedly until a condition is met
            iVar6 = headPtr;
            if (iVar6 != tailPtr) {
                do {
                    if (*(int*)(iVar6 + 0x14) != *(int*)(iVar6 + 0x1c)) {
                        do {
                            iVar3 = FUN_005246b0(); // wait for time change?
                        } while (*(int*)(iVar3 + 0x40) != *(int*)(iVar6 + 0x1c));
                    }
                    iVar6 = *(int*)(iVar6 + 0x2c); // next object
                } while (iVar6 != tailPtr);
                if (g_focusSlot != 0) {
                    // Some setter call with DAT_012233a8 + 4
                    FUN_0042ed50(*(int*)(0x012233a8 + 4), g_focusSlot);
                }
            }
        }
    }

    // Iterate through linked list and call FUN_0051fc90 on each object
    iVar6 = *(int*)(this + 4);
    if (iVar6 != *(int*)(this + 0xc)) {
        do {
            FUN_0051fc90(resetFlag);
            iVar6 = *(int*)(iVar6 + 0x2c); // next object
        } while (iVar6 != *(int*)(this + 0xc));
    }

    if (g_cleanupFlag != 0) {
        FUN_0051ead0();
    }

    if (!resetFlag) {
        if ((g_pauseFlag == 0) && (iVar6 = *(int*)(this + 4), iVar6 != *(int*)(this + 0xc))) {
            do {
                FUN_0051fc40();
                iVar6 = *(int*)(iVar6 + 0x2c);
            } while (iVar6 != *(int*)(this + 0xc));
        }
        return;
    }

    // After reset, try to find the old focus slot (uVar2) in the slot array and clear its flags
    uVar4 = 0;
    do {
        if (g_slotOwners[uVar4] == uVar2) {
            if (uVar4 < 20) {
                g_slotFlags[uVar4] &= 0xfffffffc;
            }
            break;
        }
        uVar4 = uVar4 + 1;
    } while (uVar4 < 20);

    iVar6 = g_activeSlotCount;
    g_activeSlotCount = 0;
    if ((uVar2 != g_focusSlot) || (g_focusSlot = uVar2, iVar6 != 0)) {
        if (uVar2 == 0) {
            // Focus slot 0: just reset and call engine
            g_focusSlot = uVar2;
            (**(code**)(*(int*)g_engine + 0x94))(g_engine, 1, 0);
        }
        else {
            // Focus slot > 0: compute object pointer from pool
            void* objPtr;
            if (uVar2 < 0x1000) {
                objPtr = (char*)g_objectPoolBase + uVar2 * 0x38; // each pool entry 0x38 bytes
            }
            else {
                objPtr = 0;
            }
            uVar4 = *(uint*)((char*)objPtr + 0x1c); // some index from object
            if (uVar4 != 0) {
                if (uVar4 < 0x1000) {
                    objPtr = (char*)g_objectPoolBase + uVar4 * 0x38;
                }
                else {
                    objPtr = 0;
                }
            }
            localTime.u.LowPart = 0;
            if ((*(uint*)((char*)objPtr + 0xc) & 2) == 0) {
                g_focusSlot = uVar2;
                if ((*(uint*)((char*)objPtr + 0xc) & 4) == 0) {
                    piVar1 = *(int**)((char*)objPtr + 0x14);
                    if (piVar1 == 0) {
                        piVar1 = *(int**)((char*)objPtr + 0x18);
                        if (piVar1 != 0) {
                            localTime.u.LowPart = (DWORD)piVar1;
                            (**(code**)(*piVar1 + 4))(piVar1); // call vtable+4 on piVar1
                        }
                    }
                    else {
                        // vtable+0x48 call with piVar1, g_someConst, 0, &localTime
                        (**(code**)(*piVar1 + 0x48))(piVar1, g_someConst, 0, &localTime);
                    }
                }
            }
            else {
                g_focusSlot = uVar2;
                (**(code**)(**(int**)((char*)objPtr + 0x14) + 0x48))
                          (*(int**)((char*)objPtr + 0x14), g_someConst, 0, &localTime);
            }

            // Call engine with the low part of localTime as parameter
            (**(code**)(*(int*)g_engine + 0x94))(g_engine, 1, localTime.u.LowPart);
            if ((void*)localTime.u.LowPart != 0) {
                (**(code**)(*(int*)localTime.u.LowPart + 8))(localTime.u.LowPart);
            }
        }
    }

    // Calculate delta time from last measurement
    QueryPerformanceCounter(&localTime);
    if ((g_lastTime.u.HighPart <= (uint)localTime.u.HighPart) &&
        ((g_lastTime.u.HighPart < (uint)localTime.u.HighPart ||
          (g_lastTime.u.LowPart < localTime.u.LowPart)))) {
        // No overflow: delta = current - last
        g_deltaTime.u.LowPart = localTime.u.LowPart - g_lastTime.u.LowPart;
        g_deltaTime.u.HighPart = (localTime.u.HighPart - g_lastTime.u.HighPart) -
                                  (uint)(localTime.u.LowPart < g_lastTime.u.LowPart);
        return;
    }
    // Overflow case: delta = ~(last - current) + 1 (two's complement)
    g_deltaTime.u.LowPart = ~(g_lastTime.u.LowPart - localTime.u.LowPart) + 1;
    g_deltaTime.u.HighPart = ~((g_lastTime.u.HighPart - localTime.u.HighPart) -
                                (uint)(g_lastTime.u.LowPart < localTime.u.LowPart)) +
                              (uint)(0xfffffffe < (uint)~(g_lastTime.u.LowPart - localTime.u.LowPart));
    return;
}