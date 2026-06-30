// FUNC_NAME: Allocator::constructTriple

void __thiscall Allocator::constructTriple(int* param_2) {
    // param_1 (this) is the allocator object.
    // Field at offset 0x4: fallback pointer (likely a cached allocation or null).
    int* allocPtr = (int*)this->field_0x4;  // +0x04: fallback memory pointer

    // Local stack storage if fallback is null.
    int stackBuf[3] = {0, 0, 0};  // local_c, local_8, local_4

    if (allocPtr == nullptr) {
        allocPtr = stackBuf;
    }

    // Call vtable function with size 12 (3 ints) and the fallback/stack pointer.
    // The vtable function returns a pointer to newly allocated memory (or reuses the fallback).
    allocPtr = (int*)(this->vtable->allocate)(12, allocPtr);

    if (allocPtr != nullptr) {
        allocPtr[0] = 0;             // First field set to zero
        allocPtr[1] = 0;             // Second field originally set to unaff_retaddr (likely a third param that was not captured). Assuming 0 for safety.
        allocPtr[2] = *param_2;      // Third field copies first int from source
    }
    // Note: The original decompiled code sets allocPtr[1] = unaff_retaddr, which is likely a third parameter passed in a register (e.g., edx in __fastcall).
    // That value is not available in the current signature. It is omitted here.
}