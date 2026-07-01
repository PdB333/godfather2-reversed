// FUNC_NAME: UnknownObject::~UnknownObject
// Address: 0x00774f30
// Destructor for an engine object with child management. Sets vtable pointer, then cleans up
// a child object (offset +0x5C), calls a virtual cleanup on a sub-object if certain conditions
// are met, frees two heap blocks, and invokes a global cleanup routine.
void __thiscall UnknownObject::destructor(UnknownObject* this) // __fastcall in decompiler, but __thiscall for member function
{
    // vtable assignment (common in EARS engine destructors)
    this->vtable = (void**)&g_vtable_00d67f24; // +0x00

    int* childPtr = this->m_pChild; // +0x5C (param_1[0x17])
    if (childPtr != nullptr && childPtr != (int*)0x48 && !(this->m_flags & 0x20)) // m_flags at +0x64 (param_1[0x19])
    {
        int* basePtr;
        if (childPtr == 0)
            basePtr = 0;
        else
            basePtr = (int*)((char*)childPtr - 0x48); // subtract size of header (0x48)

        // Check pointer at offset 300 bytes from base (0x12C) and virtual call at vtable+0x1c
        if (basePtr != nullptr && basePtr[75] != 0 && basePtr[75] != (int)0x48) // basePtr[75] == *(int*)(base + 300)
        {
            void* subObj = (void*)basePtr[74]; // basePtr[74] == *(int*)(base + 0x128)
            // Call virtual function at vtable+0x1c on subObj, passing basePtr as argument
            (*(void (__thiscall **)(void*, int*))(*(int*)subObj + 0x1C))(subObj, basePtr);
        }
    }

    if (childPtr != nullptr)
        operatorDelete(childPtr); // FUN_004daf90

    if (this->m_pOther != nullptr) // +0x54 (param_1[0x15])
        operatorDelete(this->m_pOther);

    globalCleanup(); // FUN_004ac1e0 (likely deinit or release ref)
}