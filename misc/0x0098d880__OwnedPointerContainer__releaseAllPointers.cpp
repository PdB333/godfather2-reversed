// FUNC_NAME: OwnedPointerContainer::releaseAllPointers
// Function address: 0x0098d880
// This function iterates through an array of owned pointers and calls their respective release/deleter functions.
// The structure contains up to 4 pairs of (pointer, deleter) at interleaved offsets:
//   +0x00: pointer 0
//   +0x0C: function pointer (deleter) for pointer 0
//   +0x10: pointer 1
//   +0x1C: function pointer for pointer 1
//   +0x20: pointer 2
//   +0x2C: function pointer for pointer 2
//   +0x30: pointer 3
//   +0x3C: function pointer for pointer 3

void __fastcall OwnedPointerContainer::releaseAllPointers(int *thisPtr)
{
    // Release in reverse order (index 3 down to 0) to avoid dependency issues
    if (thisPtr[0xc] != 0) {
        // Call deleter at +0x3C on pointer at +0x30
        ((void (*)(void*))thisPtr[0xf])((void*)thisPtr[0xc]);
    }
    if (thisPtr[8] != 0) {
        // Call deleter at +0x2C on pointer at +0x20
        ((void (*)(void*))thisPtr[0xb])((void*)thisPtr[8]);
    }
    if (thisPtr[4] != 0) {
        // Call deleter at +0x1C on pointer at +0x10
        ((void (*)(void*))thisPtr[7])((void*)thisPtr[4]);
    }
    if (thisPtr[0] != 0) {
        // Call deleter at +0x0C on pointer at +0x00
        ((void (*)(void*))thisPtr[3])((void*)thisPtr[0]);
    }
}