// FUNC_NAME: Stack::pushElementFromBuffer
// Address: 0x006260b0
// This function copies an 8-byte element from a buffer (indexed by param_2 or from a fallback source) onto the top of a stack.
// The stack structure is pointed to by param_3 and has the following layout:
//   +0x00: ??? (unused)
//   +0x08: current top pointer (offset/address) within the stack
//   +0x0c: pointer to the base of the source buffer (array of 8-byte entries)

void __fastcall Stack::pushElementFromBuffer(
    // In __fastcall, param_1 is in ECX (unused here, possibly this in a different context)
    int unused,                // param_1 - not used
    int index,                // param_2 - index into source buffer (if >= 1)
    Stack* stack,             // param_3 - pointer to stack structure
    float extraFloat          // param_4 - passed as float; used in a special case
    )
{
    int sourceAddr;           // calculated from index and stack buffer
    int elementID;            // from sourceAddr + 4
    int topPtr;               // current top of stack (from stack + 0x08)
    int* destPtr;            // target address for the push (returned by FUN_00637f10)
    int pushSize[2];          // temporary structure for push operation (size = 8 bytes?)

    // Determine the source address for the element to copy
    if (index < 1) {
        // If index is invalid (<1), fallback to some function (e.g., "getDefaultElement")
        sourceAddr = FUN_00625430();  // returns a pointer to a static element?
    }
    else {
        // Compute address from buffer start + (index-1)*8
        // Buffer start is at stack + 0x0c
        sourceAddr = *(int*)(stack + 0x0c) + (-8) + index * 8;
    }

    // Read an identifier/ID from the source (offset +4)
    elementID = *(int*)(sourceAddr + 4);

    // Get the current top pointer from the stack structure
    topPtr = *(int*)(stack + 0x08);

    // Ask for a destination address (likely the next free slot or a validation step)
    destPtr = (int*)FUN_00637f10();  // returns a pointer where we can write

    // Special case: if the returned pointer equals a global sentinel value (DAT_00e2a93c)
    if (destPtr == &DAT_00e2a93c) {
        // Prepare a push descriptor with the extra float and size=3
        pushSize[0] = 3;              // local_10 = 3
        *(float*)&pushSize[1] = extraFloat; // local_c = extraFloat (float stored at offset 1?)

        // Perform a special push operation that may involve the elementID and the push descriptor
        FUN_00637d60(stack, elementID, pushSize);
    }

    // Copy two 4-byte values from the current top (actually from top-8 and top-4) into the destination
    destPtr[0] = *(int*)(topPtr - 8);   // copy value at [top-8]
    destPtr[1] = *(int*)(topPtr - 4);   // copy value at [top-4]

    // Update the stack's top pointer (decrement by 8, since we pushed an 8-byte element)
    *(int*)(stack + 0x08) = topPtr - 8;
}