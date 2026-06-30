// FUNC_NAME: EAString::assign
// Function address: 0x004d5210
// Role: Assigns a C-string to an EAString object, releasing old heap buffers if any.
// Structure fields (this): +0x00 = data pointer (internal or heap), +0x04 = capacity/size, +0x08 = something else
// Parameters: src (char*), oldBuf1 (uint*), oldBuf2 (uint*) – pointers to old heap buffers to free.
// Recursive call handles self-assignment (this == oldBuf1 or this == oldBuf2) by swapping.

bool __thiscall EAString::assign(uint* thisString, char* src, uint* oldBuf1, uint* oldBuf2)
{
    bool success = false;
    char local;

    local = 0;

    // Avoid self-assignment: if thisString overlaps with oldBuf1 or oldBuf2, handle via recursion
    if ((thisString != oldBuf1) && (thisString != oldBuf2)) {
        // Release old buffer 1 if it exists (vtable at +12)
        if (*oldBuf1 != 0) {
            (*(void (__thiscall*)(uint*))oldBuf1[3])(oldBuf1);
        }
        *oldBuf1 = 0;
        oldBuf1[2] = 0;
        oldBuf1[1] = 0;

        // Release old buffer 2 if it exists
        if (*oldBuf2 != 0) {
            (*(void (__thiscall*)(uint*))oldBuf2[3])(oldBuf2);
        }
        *oldBuf2 = 0;
        oldBuf2[2] = 0;
        oldBuf2[1] = 0;

        // If the current string has non-zero capacity (+4)
        if (thisString[1] != 0) {
            uint dataPtr = *thisString;                       // +0x00
            uint capacity = stringBufferSize(dataPtr);         // FUN_004d4e20
            if (capacity != 0) {
                // Zero out the tail of the buffer if dataPtr < capacity
                if (dataPtr < capacity) {
                    memZero(dataPtr, 0, capacity - dataPtr);   // FUN_004d3f10
                }

                // Compute the length of the source string
                char* pcVar1 = src + 1;
                while (*src != '\0') {
                    src++;
                }
                // Adjust src pointer to a new position based on capacity and original length
                src = src + (capacity - (uint)pcVar1);

                // If the new position is not null-terminated, zero out the remainder
                if (*src != '\0') {
                    memZero(src, 0, (thisString[1] - (uint)src) + *thisString); // FUN_004d3f10
                }

                success = true; // local_11 = 1
            }
        }
        return success;
    }

    // Self-assignment case: release this string and recursively assign with swapped parameters
    releaseString(thisString);                             // FUN_004d3b50
    success = EAString::assign(src, oldBuf1, oldBuf2);     // Recursive call (note: first param changed)
    return success;
}