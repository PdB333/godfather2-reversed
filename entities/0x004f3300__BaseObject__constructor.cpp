// FUNC_NAME: BaseObject::constructor
undefined4* BaseObject::constructor(int pParentOrFlags, undefined4* pObjectMemory)
{
    if (pObjectMemory != nullptr)
    {
        // Call base class constructor or initialization routine
        callBaseConstructor(); // FUN_00533cc0

        // Set the vtable pointer to the object's vtable
        *pObjectMemory = &VTABLE_BaseObject; // PTR_FUN_00e37670

        // Check if the parent/context object has not been initialized (byte at +0x0D)
        if (*(char*)(pParentOrFlags + 0xD) == '\0')
        {
            // Perform first-time initialization
            performFirstTimeInit(); // FUN_004f3780
        }

        return pObjectMemory;
    }

    return nullptr;
}