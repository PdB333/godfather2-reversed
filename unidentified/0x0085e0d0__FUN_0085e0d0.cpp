// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(SomeClass* this)
{
    int* pMemberPtr = reinterpret_cast<int*>(this + 2); // +0x08: pointer to allocated memory

    // Set vtable to derived class vtable
    *reinterpret_cast<void**>(this) = &PTR_FUN_00d75650;

    // If the member pointer is non-null and not a sentinel value (0x48)
    if (*pMemberPtr != 0 && *pMemberPtr != 0x48)
    {
        // Call sub-destructor (likely frees internal resources)
        subDestructor();

        // If still non-null, free the memory and clear pointer
        if (*pMemberPtr != 0)
        {
            operatorDelete(pMemberPtr);
            *pMemberPtr = 0;
        }
    }

    // Release global shared resources (likely reference-counted singletons)
    releaseGlobalResource(&DAT_0112df84);
    releaseGlobalResource(&DAT_0112df90);
    releaseGlobalResource(&DAT_0112df64);

    // Final check: free memory if still allocated
    if (*pMemberPtr != 0)
    {
        operatorDelete(pMemberPtr);
    }

    // Set vtable to base class vtable (destructor chaining)
    *reinterpret_cast<void**>(this) = &PTR_LAB_00d75630;
}