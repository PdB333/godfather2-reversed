// FUNC_NAME: MultiplayerScenarioManager::MultiplayerScenarioManager

#include "EARSFramework.h"
#include "MultiplayerScenarioManager.h"

// Address: 0x008a5570
// Role: Constructor for MultiplayerScenarioManager. Initializes base classes, registers message handlers
// for scenario start/complete, and creates an embedded sub-object.

void __thiscall MultiplayerScenarioManager::MultiplayerScenarioManager(void* thisPtr)
{
    // Get global manager singleton or memory pool
    unknown_type* pGlobal = FUN_009c89c0();
    FUN_004bef20(pGlobal);

    // Store global pointer for later use
    pGlobal = DAT_00d5c454;

    // Set vtable pointers for multiple inheritance (bases at +0x00 and +0x04)
    *(void**)thisPtr = &PTR_LAB_00d79828;      // Base1 vtable (likely EARS::Framework::Object)
    *(void**)((int)thisPtr + 4) = &PTR_LAB_00d79824;  // Base2 vtable (e.g., IMessageHandler)

    // Initialize embedded sub‑object at offset 0xd8 (0x360 bytes)
    *(void**)((int)thisPtr + 0x360) = &PTR_LAB_00d79814;  // Sub‑object vtable

    // Field at +0x378 (0xde * 4) set to -1 (invalid handle / index)
    *(int*)((int)thisPtr + 0x378) = -1;

    // Clear various flags and counters
    *(int*)((int)thisPtr + 0x37C) = 0;   // +0xdf
    *(char*)((int)thisPtr + 0x380) = 0;  // +0xe0 (byte field)
    *(int*)((int)thisPtr + 0x384) = 0;   // +0xe1
    *(int*)((int)thisPtr + 0x388) = 0;   // +0xe2
    *(int*)((int)thisPtr + 0x38C) = 0;   // +0xe3
    *(int*)((int)thisPtr + 0x390) = 0;   // +0xe4

    // Register this manager with a global subsystem (slot 6)
    FUN_008a4610(6, pGlobal);

    // Field at +0x3D4 (0xf5*4)
    *(int*)((int)thisPtr + 0x3D4) = 0;

    // Allocate a sub‑object of size 0x5C and initialize it
    void* pSubObj = FUN_009c8e50(0x5C);
    if (pSubObj != NULL)
    {
        FUN_008b00a0(pSubObj);  // Sub‑object constructor
    }

    // Register message handlers for multiplayer scenario events
    FUN_00408680(&DAT_01206a20);                  // Register message table
    FUN_00408240(&DAT_0112ee84, "iMsgMultiplayerScenarioStarting");
    FUN_00408240(&DAT_0112ee7c, "iMsgMultiplayerScenarioCompleted");
    FUN_00408680(&DAT_0112ee7c);                  // Complete registration

    // Additional field initializations
    *(int*)((int)thisPtr + 0x394) = 0;   // +0xe5
    *(int*)((int)thisPtr + 0x398) = 0;   // +0xe6
    *(int*)((int)thisPtr + 0x3A8) = 0;   // +0xea
    *(int*)((int)thisPtr + 0x3A4) = 0;   // +0xe9
    *(int*)((int)thisPtr + 0x3A0) = 0;   // +0xe8
    *(int*)((int)thisPtr + 0x3AC) = 0;   // +0xeb
    *(int*)((int)thisPtr + 0x3B0) = 0;   // +0xec
    *(int*)((int)thisPtr + 0x39C) = 0;   // +0xe7
    *(int*)((int)thisPtr + 0x3B4) = -1;  // +0xed
    *(int*)((int)thisPtr + 0x3B8) = -1;  // +0xee

    return;
}