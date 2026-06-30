// FUNC_NAME: ResourceHolder::~ResourceHolder

void __thiscall ResourceHolder::~ResourceHolder()
{
    // Set vtable to current class vtable to ensure proper virtual dispatch during destruction
    // +0x00: vtable pointer
    *(void**)this = (void*)&ResourceHolder_vtable;  // PTR_FUN_00d5d89c

    // Check if resource pointer at offset +0x0C is non-null
    if (*(void**)((char*)this + 0x0C) != 0)
    {
        // Release the resource (likely a heap-allocated buffer or reference-counted object)
        releaseData((void**)((char*)this + 0x0C));  // calls FUN_004daf90
    }

    // Reset vtable to purecall to prevent any further virtual function calls after destruction
    // +0x00: vtable pointer
    *(void**)this = (void*)&_purecall_vtable;  // PTR___purecall_00e407a4
}