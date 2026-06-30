// FUNC_NAME: CStreamManager::~CStreamManager
// Function at 0x00621750 - Destructor for a stream manager/task object.
// The object layout (offsets from this):
// +0x00: unknown (may be base class pointer)
// +0x04: vtable pointer (this class virtuals)
// +0x14: pointer to a sub-object with its own vtable (possibly a task/base container)
// +0x18: pointer to an array/list that is released
// +0x1c: pointer to another sub-object (size 0x28 bytes) released via vtable[1]
// +0x20: extra pointer set to null

void __thiscall CStreamManager::~CStreamManager(CStreamManager *this)
{
    char localBuffer[12]; // small buffer passed to helper, seemingly unused

    // Call an internal cleanup helper (likely memory pool deallocation or ref counting)
    // Parameters: buffer, this, the double-pointer at offset 0x1c, this again, same pointer
    FUN_00622b80(localBuffer, this, **(void***)((char*)this + 0x1c), this, *(void***)((char*)this + 0x1c));

    // Virtual call through this's vtable (index 1) to destroy the sub-object at +0x1c (size 0x28 = 40 bytes)
    // The sub-object is freed by calling this->vtable[1](ptr, 0x28)
    void **vtable = *(void***)((char*)this + 4); // vtable pointer at offset 4
    ((void (__thiscall*)(void*, int))vtable[1])(*(void**)((char*)this + 0x1c), 0x28);

    // Clear the sub-object pointer and adjacent member
    *(int*)((char*)this + 0x1c) = 0;
    *(int*)((char*)this + 0x20) = 0;

    // If the array pointer at offset 0x18 is not null, release it via the sub-object at +0x14
    if (*(int*)((char*)this + 0x18) != 0) {
        // Virtual call on the sub-object at +0x14 (vtable index 1) to free the array with flag 0
        void **subVtable = *(void***)(*(int*)((char*)this + 0x14));
        ((void (__thiscall*)(void*, int))subVtable[1])(*(void**)((char*)this + 0x18), 0);
        *(int*)((char*)this + 0x18) = 0;
    }

    // Virtual call on the sub-object at +0x14 (vtable index 3) - likely its own destructor/cleanup
    void **subVtable2 = *(void***)(*(int*)((char*)this + 0x14));
    ((void (__thiscall*)(void*))subVtable2[3])();

    // Global cleanup routine (e.g., task manager shutdown)
    FUN_00621f30();
}