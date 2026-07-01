// FUNC_NAME: CollisionPairManager::removeObject

// Struct representing a collision pair entry (12 bytes total)
struct CollisionPair {
    void* m_pObjectA;      // +0x00: first object in collision pair
    void* m_pObjectB;      // +0x04: second object
    void* m_pCallback;     // +0x08: pointer to a callback object (vtable with virtual method taking int)
};

// Removes all references to the given object from the collision pair manager.
// The object is identified by its unique ID (four ints at +0x24, +0x28, +0x2c, +0x30).
// Offsets in this:
//   +0x10: active collision object A (secondary)
//   +0x14: active collision object B (primary)
//   +0x18: state (0=idle, 1/2=active)
//   +0x70: related state variable
//   +0x8c: pointer to array of CollisionPair entries
//   +0x90: number of valid entries in the array
void __thiscall CollisionPairManager::removeObject(void* this, void* object) {
    // Release primary active object if it matches
    void* primary = *(void**)((char*)this + 0x14);
    if (primary != nullptr &&
        *(int*)((char*)object + 0x24) == *(int*)((char*)primary + 0x24) &&
        *(int*)((char*)object + 0x28) == *(int*)((char*)primary + 0x28) &&
        *(int*)((char*)object + 0x2c) == *(int*)((char*)primary + 0x2c) &&
        *(int*)((char*)object + 0x30) == *(int*)((char*)primary + 0x30)) {
        FUN_00827830(); // releaseReference(primary)
        *(void**)((char*)this + 0x14) = nullptr;
        int state = *(int*)((char*)this + 0x18);
        if (state == 1 || state == 2) {
            *(int*)((char*)this + 0x18) = 0;
            *(int*)((char*)this + 0x70) = 0;
        }
    }

    // Release secondary active object if it matches
    void* secondary = *(void**)((char*)this + 0x10);
    if (secondary != nullptr &&
        *(int*)((char*)object + 0x24) == *(int*)((char*)secondary + 0x24) &&
        *(int*)((char*)object + 0x28) == *(int*)((char*)secondary + 0x28) &&
        *(int*)((char*)object + 0x2c) == *(int*)((char*)secondary + 0x2c) &&
        *(int*)((char*)object + 0x30) == *(int*)((char*)secondary + 0x30)) {
        FUN_00827830(); // releaseReference(secondary)
        *(void**)((char*)this + 0x10) = nullptr;
        int state = *(int*)((char*)this + 0x18);
        if (state == 1 || state == 2) {
            *(int*)((char*)this + 0x18) = 0;
            *(int*)((char*)this + 0x70) = 0;
        }
    }

    // Process dynamic collision pair array
    uint entryCount = *(uint*)((char*)this + 0x90);
    CollisionPair* pairs = *(CollisionPair**)((char*)this + 0x8c);
    uint i = 0;
    while (i < entryCount) {
        CollisionPair* entry = &pairs[i];
        bool cleared = false;

        // Check object A
        if (entry->m_pObjectA != nullptr &&
            *(int*)((char*)entry->m_pObjectA + 0x24) == *(int*)((char*)object + 0x24) &&
            *(int*)((char*)entry->m_pObjectA + 0x28) == *(int*)((char*)object + 0x28) &&
            *(int*)((char*)entry->m_pObjectA + 0x2c) == *(int*)((char*)object + 0x2c) &&
            *(int*)((char*)entry->m_pObjectA + 0x30) == *(int*)((char*)object + 0x30)) {
            entry->m_pObjectA = nullptr;
        }

        // Check object B
        if (entry->m_pObjectB != nullptr &&
            *(int*)((char*)entry->m_pObjectB + 0x24) == *(int*)((char*)object + 0x24) &&
            *(int*)((char*)entry->m_pObjectB + 0x28) == *(int*)((char*)object + 0x28) &&
            *(int*)((char*)entry->m_pObjectB + 0x2c) == *(int*)((char*)object + 0x2c) &&
            *(int*)((char*)entry->m_pObjectB + 0x30) == *(int*)((char*)object + 0x30)) {
            entry->m_pObjectB = nullptr;
        }

        // If the callback is not one of the active objects, we need to remove and notify
        if (entry->m_pCallback != primary && entry->m_pCallback != secondary) {
            if (entry->m_pCallback != nullptr) {
                // Callback's vtable: first virtual function with argument 1 (e.g., onCollisionEnd)
                (**(void (__thiscall**)(void*, int))entry->m_pCallback)(entry->m_pCallback, 1);
            }
            // Clear the entire entry
            entry->m_pObjectA = nullptr;
            entry->m_pObjectB = nullptr;
            entry->m_pCallback = nullptr;

            // Shift last entry into this position if not already last
            uint currentCount = *(uint*)((char*)this + 0x90);
            if (i != currentCount - 1) {
                CollisionPair* last = &pairs[currentCount - 1];
                *entry = *last;  // copy 12 bytes
            }
            *(uint*)((char*)this + 0x90) = currentCount - 1;
            cleared = true;
        }

        // If we cleared the entry via shifting, do not advance i (reprocess same index)
        if (!cleared) {
            i++;
        }
        // Re-read entryCount because it may have changed
        entryCount = *(uint*)((char*)this + 0x90);
    }
}