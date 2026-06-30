// FUNC_NAME: BaseObject::deletingDestructor
// Address: 0x00561740
// Role: Scalar deleting destructor for BaseObject. Calls internal cleanup and optionally frees aligned memory.

extern void* PTR_LAB_00d996b0;       // vtable for BaseObject
extern void internalCleanup(void);  // FUN_00aa2650
extern void* _aligned_free;         // pointer to aligned free function at 0x00ef3e60

void* __thiscall BaseObject::deletingDestructor(void* thisPointer, unsigned char flags) {
    // Set vtable pointer (base class vtable at 0x00d996b0)
    *(void**)thisPointer = &PTR_LAB_00d996b0;

    // Call the actual destructor body (cleanup logic)
    internalCleanup();

    // If the low bit of flags is set, deallocate memory
    if ((flags & 1) != 0) {
        (*(void(__stdcall*)(void*))_aligned_free)(thisPointer);
    }

    return thisPointer;
}