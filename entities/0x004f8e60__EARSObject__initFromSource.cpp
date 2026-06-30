// FUNC_NAME: EARSObject::initFromSource
#include <cstdint>

// Address: 0x004f8e60
// This function initializes an EARSObject from a source object
// Uses thread-local storage to copy three ints from source to a global buffer

#define PTR_FUN_00e379c8 ((void*)0x00e379c8) // placeholder vtable pointer

void __thiscall EARSObject::initFromSource(void* this, void* source)
{
    // Calls base initialization (likely sets up class-specific data)
    sub_533cc0();

    // Set virtual function table
    *(intptr_t**)this = (intptr_t*)PTR_FUN_00e379c8;

    // Check if the object's flag at +0xD is zero
    if (*(char*)((uintptr_t)this + 0xD) == 0)
    {
        // Copy source pointer to field at +0x24
        *(void**)((uintptr_t)this + 0x24) = source;

        // Copy int from source+0x24 to field at +0x2C
        *(int*)((uintptr_t)this + 0x2C) = *(int*)((uintptr_t)source + 0x24);

        // Conditional: if source+0x20 is zero, use source+0x1C; else set to 0
        if (*(float*)((uintptr_t)source + 0x20) == 0.0f)
        {
            *(int*)((uintptr_t)this + 0x28) = *(int*)((uintptr_t)source + 0x1C);
        }
        else
        {
            *(int*)((uintptr_t)this + 0x28) = 0;
        }

        // Retrieve thread-local storage pointer (FS:[0x2C])
        // In Windows, this is the Thread Information Block (TIB) pointer
        int* tls = **(int***)(__readfsdword(0x2C));

        // Index from this object at +0x10 (field_0x10)
        int idx = *(int*)((uintptr_t)this + 0x10);

        // Clear fields at +0x34 and +0x30
        *(int*)((uintptr_t)this + 0x34) = 0;
        *(int*)((uintptr_t)this + 0x30) = 0;

        // Calculate buffer address: tls[8] + 0x40 + idx
        int* buffer = (int*)(*(int*)((uintptr_t)tls + 8) + 0x40 + idx);

        // Copy three ints from source+4, source+8, source+0xC into buffer
        buffer[0] = *(int*)((uintptr_t)source + 4);
        buffer[1] = *(int*)((uintptr_t)source + 8);
        buffer[2] = *(int*)((uintptr_t)source + 0xC);
    }
}

// Note: In the original binary, the function sub_533cc0 is called first.
// Its purpose is unknown but likely does base class initialization.