// FUNC_NAME: BaseClass::~BaseClass
// Destructor for a base class (likely from EARS engine). 
// Calls destructors on two embedded sub-objects (at +0x0C and +0x1C) using their vtable function pointers,
// then resets the vtable to a sentinel to prevent further virtual calls,
// and optionally deallocates memory if the flags parameter indicates deletion.
void __thiscall BaseClass::~BaseClass(void* this, byte flags)
{
    // Call destructor for sub-object at +0x0C (function pointer at +0x18)
    if (*(void**)((uint)this + 0x0C) != 0)
    {
        (*(void(__thiscall**)(void*))(*(int*)this + 0x18))(*(void**)((int)this + 0x0C));
    }
    // Call destructor for sub-object at +0x1C (function pointer at +0x28)
    if (*(void**)((uint)this + 0x1C) != 0)
    {
        (*(void(__thiscall**)(void*))(*(int*)this + 0x28))(*(void**)((int)this + 0x1C));
    }
    // Set vtable to base class sentinel (prevents further virtual dispatch)
    *(int*)this = (int)&PTR_LAB_00d576d4; // Sentinal vtable pointer
    // If deletion flag (bit 0) is set, free this object's memory
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this); // Memory deallocation (operator delete or custom allocator)
    }
}