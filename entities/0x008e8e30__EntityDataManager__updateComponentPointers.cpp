// FUNC_NAME: EntityDataManager::updateComponentPointers
int __thiscall EntityDataManager::updateComponentPointers(void* this, int someId) // someId likely passed in EDX, decompiler misidentified as unaff_EDI
{
    int* pComponentA = (int*)((char*)this + 0x98); // pointer to component A (offset +0x98)
    int* pComponentB; // reused for second lookup
    int componentAValue = *pComponentA;
    // Check if component A is null or a special sentinel (0x48)
    if (componentAValue == 0 || componentAValue == 0x48)
    {
        int localVar = (int)this;
        // Lookup component by hash via a virtual method on some manager at offset +0x54
        int* manager = (int*)FUN_00446100((char*)this + 0x54, 0); // likely a hash table or component manager
        localVar = 0;
        char result = (*(char (__thiscall**)(int, int*))(*(int*)manager + 0x10))(0xd7e44d6a, &localVar); // virtual call with hash
        // someId (unaff_EDI) is used to mask the result; if result is nonzero, use someId
        unsigned int masked = -(result != 0) & (unsigned int)someId;
        int newComponentA;
        if (masked == 0)
            newComponentA = 0;
        else
            newComponentA = masked + 0x48; // offset by 0x48 (header size?)
        // Update component A pointer with linked list management
        if (*pComponentA != newComponentA)
        {
            if (*pComponentA != 0)
                FUN_004daf90(pComponentA); // release old pointer
            *pComponentA = newComponentA;
            if (newComponentA != 0)
            {
                *(int*)((char*)this + 0x9c) = *(int*)(newComponentA + 4); // store next pointer
                *(int**)(newComponentA + 4) = pComponentA; // link back
            }
        }
        // Second component (offset +0xa0) from a global singleton
        int globalObj = FUN_00791300(); // likely returns a global object pointer
        int newComponentB;
        if (globalObj == 0)
            newComponentB = 0;
        else
            newComponentB = globalObj + 0x48;
        int* pComponentB = (int*)((char*)this + 0xa0);
        if (*pComponentB != newComponentB)
        {
            if (*pComponentB != 0)
                FUN_004daf90(pComponentB);
            *pComponentB = newComponentB;
            if (newComponentB != 0)
            {
                *(int*)((char*)this + 0xa4) = *(int*)(newComponentB + 4);
                *(int**)(newComponentB + 4) = pComponentB;
            }
        }
    }
    // Return the original component A pointer (minus header offset)
    if (*pComponentA != 0)
        return *pComponentA - 0x48;
    return 0;
}