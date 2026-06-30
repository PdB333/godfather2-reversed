// FUNC_NAME: DebugSpawnManager::attemptSpawn

// Reconstructed from game binary at 0x00720820
// This function attempts to spawn a debug object (likely a marker or vehicle) at a location
// stored in the object pointed to by param_1. It performs time-gating and checks a bit flag.
// If conditions are met, it resolves a global manager pointer and spawns an object.

void __fastcall DebugSpawnManager::attemptSpawn(void* this)
{
    char cVar1;
    int parentPtr; // Derived from this->+0x4, possibly a pointer to a larger parent object
    int unknownObj;

    // Call some initialization or empty function
    FUN_00720750(0);

    // Resolve parent object: if this->+0x4 is non-null, subtract 0x48 to get the base of the parent
    if (*(int*)((int)this + 4) == 0) {
        parentPtr = 0;
    } else {
        parentPtr = *(int*)((int)this + 4) - 0x48;
    }

    // Check if a timer or cooldown (at offset 0x1eb4 in parent) has expired
    // global DAT_01205224 is likely the current frame count or game time
    if (*(int*)(parentPtr + 0x1eb4) != 0) {
        // Re-derive parentPtr (same logic)
        if (*(int*)((int)this + 4) == 0) {
            parentPtr = 0;
        } else {
            parentPtr = *(int*)((int)this + 4) - 0x48;
        }
        // If current time < (stored time + 300), bail to spawn label
        if (DAT_01205224 < *(int*)(parentPtr + 0x1eb4) + 300U) goto LAB_00720879;
    }

    // Re-derive parentPtr again
    if (*(int*)((int)this + 4) == 0) {
        parentPtr = 0;
    } else {
        parentPtr = *(int*)((int)this + 4) - 0x48;
    }
    // Check bit 0 of a flag at offset 0x8e6 in parent; if clear, abort
    if ((*(byte*)(parentPtr + 0x8e6) & 1) == 0) {
        return;
    }

LAB_00720879:
    // Resolve global manager pointer at DAT_012233a0
    // It points to a pointer-to-pointer structure; dereference twice, then check sanity
    unknownObj = **(int**)(DAT_012233a0 + 4); // This loads a pointer from global table
    if (unknownObj != 0 &&
        unknownObj != 0x1f30 && // Some magic value, possibly a null/invalid sentinel
        // Subtract 0x1d18 to get another object pointer
        (unknownObj = *(int*)(unknownObj - 0x1d18), unknownObj != 0) &&
        // Check another condition via function call (returns false if not allowed)
        (cVar1 = FUN_007f7c50(), cVar1 == '\0')) {
        // Call spawn function with coordinates from unknownObj+0x14 and unknownObj+0x1c
        FUN_0045f020(*(int*)(unknownObj + 0x14), *(int*)(unknownObj + 0x1c), 0, 0, 0);
    }
    return;
}