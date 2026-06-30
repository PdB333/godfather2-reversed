// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(void* thisPtr_ecx)
{
    // Set the vtable pointer to the class-specific vtable (destructor phase)
    *(int**)thisPtr_ecx = &PTR_LAB_00d653d4; // EARSObject vtable

    // If the sub-object at offset +4 exists, release it
    if (*(void**)((int)thisPtr_ecx + 4) != 0)
    {
        FUN_004daf90((int*)thisPtr_ecx + 1); // delete sub-object (likely operator delete or sub-destructor)
    }

    // Set vtable to purecall to prevent further virtual calls after destruction
    *(int**)thisPtr_ecx = &PTR___purecall_00e407a4;
}