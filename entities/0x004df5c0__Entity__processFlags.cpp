// FUNC_NAME: Entity::processFlags
void __fastcall Entity::processFlags(int* param_1)
{
    // param_1 is typically 'this' (pointer to an Entity or handle container)
    // The first field of the object is a pointer to the internal representation (e.g., SimObject)
    int objPtr = *param_1;
    if (objPtr != 0) {
        uint* flagsPtr = (uint*)(objPtr + 0xC); // +0x0C: flags field (bitmask)
        uint flags = *flagsPtr;

        // Clear bit 0x20000 (e.g., "hasPendingDestroy" or "onSimManager")
        *flagsPtr = flags & 0xFFFDFFFF;

        if ((flags & 0x80000) != 0) { // Check bit 0x80000 (e.g., "dirtyFlags" or "needsUpdate")
            // Clear bit 0x80000
            flags &= 0xFFF7FFFF;

            // If the low bit (0x1) is set AND the object's type/vtable indicates it can handle something specific,
            // set the high bit (0x80000000) as an urgent flag.
            if ((flags & 1) != 0) {
                int* vtableOrClassData = *(int**)(objPtr + 0x10); // +0x10: pointer to class info / vtable
                if (vtableOrClassData != nullptr) {
                    uint classFlags = *(uint*)(*vtableOrClassData + 0x14); // +0x14: class capability flags
                    if ((classFlags & 0x20000000) != 0) {
                        flags |= 0x80000000; // Urgent processing needed
                    }
                }
            }

            *flagsPtr = flags;

            // Notify the object that its flags have changed (e.g., call onFlagsChanged or processUpdate)
            FUN_0051b0b0(objPtr);
        }
    }
}