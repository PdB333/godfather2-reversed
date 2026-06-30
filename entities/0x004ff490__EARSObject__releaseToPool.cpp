// FUNC_NAME: EARSObject::releaseToPool

#include <cstdint>

// Global pool manager singleton (DAT_01206880)
// Structure at base +0x14: pointer to current free list cursor (grows upward)
extern void* gPoolManager;

// Vtable for dead objects (PTR_LAB_011252c4)
extern void* gDeadObjectVtable;

// Forward declaration of the sub-object release function (FUN_004ff430)
void EARSObject::releaseChildObject(void* childPtr);

// Reconstructed function: returns this object to an object pool.
void __fastcall EARSObject::releaseToPool(void* thisPtr) {
    // Check if a child object exists at offset +0x28
    if (*(void**)((char*)thisPtr + 0x28) != 0) {
        EARSObject::releaseChildObject(thisPtr);  // Release the child first
    }

    // Pointer to current free list cursor (stored at gPoolManager + 0x14)
    int* freeListCursorPtr = (int*)((char*)gPoolManager + 0x14);   // +0x14

    // Write dead vtable marker into the memory that freeListCursorPtr points to.
    // This overwrites the vtable of the object that will be placed here.
    **(int**)((char*)gPoolManager + 0x14) = (int)&gDeadObjectVtable;

    // Advance the cursor by 4 (past the vtable write)
    *freeListCursorPtr += 4;

    // Align the new cursor to a 4-byte boundary
    int* alignedCursor = (int*)(*freeListCursorPtr + 3U & 0xFFFFFFFC);

    // Store the aligned cursor back into the pool manager
    *freeListCursorPtr = (int)alignedCursor;

    // Write 'this' (the object being freed) into the aligned slot
    *alignedCursor = (int)thisPtr;

    // Advance the cursor past the stored pointer
    *freeListCursorPtr += 4;
}