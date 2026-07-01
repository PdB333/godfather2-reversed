// FUNC_NAME: PtrArray::~PtrArray (or possibly release/destroy, but behavior matches destructor)
// Function address: 0x0082b7a0
// Role: Destructor for a class that owns a dynamic array of pointers to objects.
// The object layout:
//   +0x00 : vtable pointer
//   +0x08 : pointer to array of object pointers (void**)
//   +0x0C : count of entries in the array (int)
// Calls a virtual function (index 0, likely "release") on each non‑null entry,
// then frees the array memory via FUN_009c8f10 (memory deallocator).

void __fastcall PtrArray::destroy(PtrArray* this)
{
    uint count;
    uint i;
    void** array;
    void* ptr;

    // Set vtable pointer to a zombie/dummy vtable (PTR_FUN_00d73864)
    // This prevents the vtable from being used after the destructor runs.
    *(void**)this = (void*)&PTR_FUN_00d73864;

    array = *(void***)((char*)this + 8);   // param_1[2] at +0x08
    count = *(uint*)((char*)this + 0xC);  // param_1[3] at +0x0C

    if (count != 0) {
        for (i = 0; i < count; i++) {
            ptr = array[i];
            if (ptr != nullptr) {
                // Call virtual function at vtable[0] (typically a release/delete)
                // with argument 1.
                (*(void(__thiscall**)(void*, int))ptr)(ptr, 1);
            }
        }
    }

    if (array != nullptr) {
        // Free the array memory
        FUN_009c8f10(array);
    }
}