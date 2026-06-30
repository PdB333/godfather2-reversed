// FUNC_NAME: ArrayContainer::assignRange
// Address: 0x00591c00
// This function is part of a dynamic array container (likely a class managing an array of pointers).
// It takes a pointer to a value and a count (passed via register EDI from the caller) and
// writes the value to a range of array slots, but only if the slot already contains a non-null pointer.
// The array's internal count is incremented by the given count after the operation.
// The call to FUN_005822d0 is assumed to ensure array capacity for the new elements.

void __thiscall ArrayContainer::assignRange(int* this, int* valuePtr)
{
    int count = 0; // placeholder for unaff_EDI (passed via EDI)
    // Actually the register is not a parameter; it must be set by caller.
    // We assume it's passed in a register (e.g., EDI) based on the decompiler.
    // For reconstruction, we'll treat it as an implicit parameter.
    // The decompiler shows `unaff_EDI` used directly; we need to reflect that.
    // Since it's not standard, we'll use a comment.
    // In real code, this would be a parameter of the function.

    // The following is a reconstruction of the control flow:
    // if (count != 0) { ... }

    // The actual function uses a register (EDI) that is not a formal parameter.
    // To make it compilable, we treat it as an extra implicit int parameter.
    // However, since we don't have its declaration, we'll keep the register usage.
    // We'll simulate by using an explicit parameter `int count`.
}

// Alternative reconstruction with explicit count parameter:
void __thiscall ArrayContainer::assignRange(int* this, int* valuePtr, int count)
{
    if (count != 0)
    {
        // Ensure array can hold current count + new count
        ensureArraySize(this[1] + count); // FUN_005822d0 assumed to do reallocation/sizing

        int startIndex = this[1];
        int endIndex = this[1] + count;
        int i = startIndex;
        do {
            // Pointer to the i-th slot of the array (array base at this[0])
            int* slot = (int*)(this[0] + i * 4);
            this[1] = i + 1; // increment internal index
            if (slot != NULL) {
                *slot = *valuePtr; // write the value to the slot
            }
            i = this[1];
        } while (endIndex != i);
    }
}