// FUNC_NAME: UnknownClass::copyConstructWithFlag
// Function address: 0x004cf4e0
// Role: Copy construction of an UnknownClass object with optional deep copy flag.
// Hidden parameter: destination object pointer passed in EDI (unaff_EDI).
// Virtual table layout (offsets from vtable pointer):
//    +0x00: destructor
//    +0x04: someAssign (param_2 = source?, param_3 = flag?)
//    +0x08: someInit
//    +0x0C: someFinalize

void UnknownClass::copyConstructWithFlag(void* dest, void* src, int flag) {
    // dest is the memory location for the new object (passed in EDI)
    // src is the source object (param_1)
    // flag indicates deep copy (non-zero) or shallow copy (zero)

    // Set the vtable pointer of the destination to the source's vtable
    *(void**)dest = src;

    // Call virtual initialization on the source (offset 0x08)
    (*(void (**)())(*(void**)src + 8))();

    if (flag != 0) {
        // Perform deep copy: call an external copy function
        // FUN_004265d0 likely copies a member (e.g., string or buffer)
        int copyResult = FUN_004265d0(flag, *(void**)dest);
        // Store the copy result at offset 0x04 in the destination object
        *(int*)((char*)dest + 4) = copyResult;
        // Call assignment virtual (offset 0x04) with source and flag
        (*(void (**)(void*, int))(*(void**)src + 4))(flag, 0);
    } else {
        // Shallow copy: clear offset 0x04
        *(int*)((char*)dest + 4) = 0;
    }
    // Call finalization virtual (offset 0x0C)
    (*(void (**)())(*(void**)src + 0x0C))();
}