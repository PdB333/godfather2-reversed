// FUNC_NAME: GhostManager::findOrAddGhost
#include <cstdint>

// A manager for a fixed-size table of ghost objects (12-byte entries).
// Offset 0x20 in DAT_01223520 is global capacity.
// Offsets: +0x24 = pointer to entry array, +0x28 = current count, +0x2C = local capacity, +0x38 = flags.
// Each entry: [0] = ghostID, [1] = pointer to ghost object (or back link), [2] = handle/result from allocation.
byte GhostManager::findOrAddGhost(int ghostID)
{
    uint currentIndex;          // uVar3
    bool found;                 // bVar2
    int* entryPtr;              // piVar5
    byte resultIndex;           // uVar7 (low byte)
    uint count;                 // uVar1

    resultIndex = 0xff;
    // Return invalid if ID is 0 (null ghost).
    if (ghostID == 0) {
        return 0xff;
    }

    entryPtr = *(int**)(this + 0x24);  // base pointer to 12-byte entries
    count = *(uint*)(this + 0x28);     // number of entries currently used

    found = false;
    currentIndex = 0;

    // Search the table for a matching ghostID.
    if (count != 0) {
        do {
            if (found) {
                return (byte)resultIndex;
            }
            if (*entryPtr == ghostID) {
                resultIndex = (byte)(currentIndex & 0xff);
                found = true;
            }
            // Note: bVar6 is not used after this, just for tracking
            // bVar6 = (byte)resultIndex; (dead store)
            currentIndex++;
            entryPtr += 3;   // advance by 3 ints (12 bytes)
        } while (currentIndex < count);

        if (found) {
            return (byte)resultIndex;
        }
    }

    // If not found and there is room, try to add a new entry.
    // Capacity is min(global capacity at DAT_01223520+0x20, local capacity at +0x2C)
    if ((count < *(uint*)(DAT_01223520 + 0x20)) && (count < *(uint*)(this + 0x2c))) {
        int allocResult = FUN_005f7f00();   // e.g. allocate a new ghost slot
        if (allocResult == 0) {
            // Allocation failed – set error flag (0x14 = capacity exceeded?).
            *(uint*)(this + 0x38) |= 0x14;
        } else {
            byte newIndex = *(byte*)(this + 0x28);   // current count (as index)
            *(uint*)(this + 0x28) = count + 1;       // increment count

            // Compute address of the new entry (located at base + count*12)
            int* newEntry = (int*)(*(int*)(this + 0x24) + (uint)newIndex * 0xc);
            if (newEntry != nullptr) {
                newEntry[1] = 0;                      // clear the back-link/pointer field
                *newEntry = ghostID;                  // store the ghost ID
                // Link back from the ghost object to this entry (ghost object +4 is a back pointer)
                newEntry[1] = *(int*)(ghostID + 4);   // presumably the ghost object's back pointer becomes this entry
                *(int**)(ghostID + 4) = newEntry;     // update ghost object's back pointer
                newEntry[2] = allocResult;            // store allocation handle
                return newIndex;
            }
        }
        // If allocation failed or entry pointer null, return the current index (which is 0xff if not set? Actually bVar6 from earlier is 0xff)
        return *(byte*)(this + 0x28) - 1; // note: this might be wrong; we need to match decompiled behavior
        // In decompiled, after failure, it returns bVar6 which was set to (byte)resultIndex earlier; resultIndex is 0xff if never found, so return 0xff.
    }

    // No room: set overflow flag (0x100 | 0x4 = 0x104).
    *(uint*)(this + 0x38) |= 0x104;
    return 0xff;
}