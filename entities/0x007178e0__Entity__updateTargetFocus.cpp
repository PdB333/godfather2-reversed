// FUNC_NAME: Entity::updateTargetFocus
uint __fastcall Entity::updateTargetFocus(int thisPtr) {
    // Offset 0x330: pointer to a sub-object (likely a child node or target handle)
    int* subObjPtr = *(int**)(thisPtr + 0x330);
    uint baseObj1 = 0;
    if (subObjPtr != nullptr) {
        baseObj1 = reinterpret_cast<uint>(subObjPtr) - 0x48; // Subtract EARS object header
    }

    // Resolve the first object (FUN_0071ce70 is likely a GetParent/Resolve function)
    uint resolved1 = 0;
    if (baseObj1 != 0) {
        resolved1 = FUN_0071ce70(baseObj1);
    }

    // Second level indirection: offset +8 from the resolved object
    if (resolved1 != 0) {
        int* childPtr = *(int**)(resolved1 + 8);
        uint baseObj2 = 0;
        if (childPtr != nullptr) {
            baseObj2 = reinterpret_cast<uint>(childPtr) - 0x48;
        }

        if (baseObj2 != 0) {
            // Compare a stored handle at +0x360 with a global constant
            if (*(int*)(thisPtr + 0x360) != DAT_01205224) {
                *(int*)(thisPtr + 0x360) = DAT_01205224;

                // Virtual call through vtable at +0x1BC, slot +0x34 (method index)
                void* vtable = *(void**)(thisPtr + 0x1BC);
                typedef char (__thiscall* Method)(void*, uint, int, int);
                Method method = *(Method*)(reinterpret_cast<uint>(vtable) + 0x34);
                char result = method(baseObj2, 0, 0);

                if (result != 0) {
                    // Set bit 7 (0x80) in flags at +0x308
                    *(uint*)(thisPtr + 0x308) |= 0x80;
                    return (*(uint*)(thisPtr + 0x308) >> 7) & 1;
                }
                // Clear bits 7 and 2 (0x84) in flags
                *(uint*)(thisPtr + 0x308) &= ~0x84;
            }
            // Return bit 7 as boolean
            return (*(uint*)(thisPtr + 0x308) >> 7) & 1;
        }
    }

    // Fallback: clear low byte of the first base pointer and return
    return baseObj1 & 0xFFFFFF00;
}