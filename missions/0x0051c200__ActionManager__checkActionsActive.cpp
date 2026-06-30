// FUNC_NAME: ActionManager::checkActionsActive

// Function address: 0x0051c200
// Role: Iterates over an array of action entries (0x10 bytes each) and
// determines if any action is currently active based on flags and resource
// availability. Returns 1 if at least one action is active, else 0.
// The function accesses per-player data (0x98 bytes per player) and uses
// thread-local storage (FS segment +0x2C) to get the current game instance.

typedef unsigned char byte;
typedef unsigned int uint;

// Forward declarations of external functions (renamed for clarity)
int __cdecl getCurrentPlayerIndex(); // FUN_004e9fa0
byte __cdecl checkActionCondition(int actionId, int param); // FUN_0051b5f0

class ActionManager
{
public:
    // Structure for an action entry (0x10 bytes)
    struct ActionEntry
    {
        int     actionId;      // +0x00: unique identifier
        int     resourceIndex; // +0x04: index into a resource list
        uint    flags;         // +0x08: bit flags (only low byte used here)
        int     unknown2;      // +0x0C: unused in this function
    };

    // The function is __thiscall; this is the implicit first parameter.
    byte checkActionsActive();

private:
    // Offsets within 'this' object:
    // +0x10: Pointer to some state object (GameState*)
    // +0x20: Reference-counted resource manager (ResourceManager*)
};

byte ActionManager::checkActionsActive()
{
    // Thread-local data: pointer retrieved from FS segment offset 0x2C
    // This is typical for accessing per-thread or per-instance globals.
    int** threadLocalBase = (int**)__readfsdword(0x2C); // Ghidra: unaff_FS_OFFSET+0x2C
    int*  gameInstance    = *threadLocalBase;            // local_4

    // Get current player index (or similar state-dependent value)
    int playerIndex = getCurrentPlayerIndex(); // iVar6

    // Determine per-player data base offset.
    // If gameInstance->playerCount (at +0x34) is non-zero, add 0x98 per player.
    int perPlayerBaseOffset = (gameInstance[0x34 / 4] != 0) ? 0x98 : 0; // iVar7

    // The count of action entries is stored at perPlayerBaseOffset + 4 + playerIndex
    int* pCount = &gameInstance[ (perPlayerBaseOffset + 4 + playerIndex) / 4 ];
    if (*pCount < 1)
    {
        return 0;
    }

    // Pointer to the first action entry (stride 0x10)
    ActionEntry* entries = (ActionEntry*)((byte*)pCount + 8); // +8 skips count and one int
    // Actually: base + perPlayerBaseOffset + 0xc + playerIndex gives address of first entry
    // Let's compute correctly: pCount points to base+perPlayerBaseOffset+4+playerIndex.
    // entries start at base+perPlayerBaseOffset+0xc+playerIndex = pCount + 2 (since 4+8=0xc)
    // So: entries = (ActionEntry*)(pCount + 2);

    byte result = 0; // local_11, will be set to 1 if any action is active

    for (int i = 0; i < *pCount; i++) // local_8 is loop index
    {
        ActionEntry* entry = &entries[i]; // puVar2 = base + i*0x10

        // Check a global flag at (this->statePtr + 0x14) bit 11 (0x800)
        byte* statePtr = *(byte**)( (byte*)this + 0x10 );
        uint  stateFlags = *(uint*)(statePtr + 0x14);
        if (!(stateFlags & 0x800))
        {
            // Normal path: check if action is valid based on flags and condition
            goto CHECK_CONDITIONS;
        }
        else
        {
            // State flag 0x800 is set: use resource manager to validate action
            // this->resourceManager (at +0x20) is a reference-counted object
            int* resourceMgr = *(int**)( (byte*)this + 0x20 );
            if (resourceMgr != NULL)
            {
                resourceMgr[1]++; // Increase reference count
            }

            int lookupResult = 0; // local_c
            if (resourceMgr != NULL)
            {
                // Call virtual function at offset 8 (lookupByHash) with hash 0x3eb08af9
                // Returns non-zero if found, and sets lookupResult to the found object
                byte found = (*(byte(__thiscall**)(int*, int*))(resourceMgr[0] + 8))(resourceMgr, &lookupResult);
                // Decrement reference count
                resourceMgr[1]--;
                if (resourceMgr[1] == 0)
                {
                    // Free resource manager (virtual destructor at +4)
                    (*(void(__thiscall**)(int*))(resourceMgr[0] + 4))(resourceMgr);
                }

                if (found)
                {
                    // If lookup succeeded, check if entry->resourceIndex is in the lookup list
                    // The lookup result object has an array at +8 with count at +0x18
                    int* lookupObj = (int*)(lookupResult); // local_c
                    if (lookupObj != NULL)
                    {
                        uint listCount = *(uint*)((byte*)lookupObj + 0x18);
                        for (uint j = 0; j < listCount; j++) // uVar8
                        {
                            if (lookupObj[2 + j] == entry->resourceIndex) // +8 + j*4
                            {
                                // resourceIndex found in list -> action is valid, fall through to CHECK_CONDITIONS
                                goto CHECK_CONDITIONS;
                            }
                        }
                        // Not found: do nothing (result stays 0 for this entry)
                        continue;
                    }
                }
            }
            // If resource manager null or lookup failed, fall through to CHECK_CONDITIONS
        }

    CHECK_CONDITIONS:
        // Check additional conditions:
        // bVar3 = statePtr[0x1D] (a byte flag)
        byte stateFlag2 = statePtr[0x1D]; // bVar3
        if (
            (
                (stateFlag2 == 0) ||
                (entry->flags == 0) ||
                ((entry->flags & stateFlag2) != 0)
            ) &&
            (checkActionCondition(entry->actionId, 0) != 0)
           )
        {
            result = 1; // At least one action is active
        }
        // If not, result remains unchanged, continue to next entry
    }

    return result;
}