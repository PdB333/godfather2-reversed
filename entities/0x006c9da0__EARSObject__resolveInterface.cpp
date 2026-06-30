// FUNC_NAME: EARSObject::resolveInterface
// Address: 0x006c9da0
// This function queries the object for specific interfaces by GUID (via vtable[0x10] which is likely a "getInterface" method),
// then performs actions on global manager objects (indicated by ESI register) or derived interfaces.
// Returns 0xFFFFFFFF (-1) on failure, otherwise returns result from called function.

int EARSObject::resolveInterface()
{
    // First attempt: interface GUID 0x383225a1
    void* interfacePtr = nullptr;
    bool hasInterface = (this->vtable[0x10])(0x383225a1, &interfacePtr);
    if (hasInterface && g_pGlobalManager != nullptr)
    {
        // Access offset 0x7CC from the global manager (likely an array or list of objects)
        // then call a virtual function at offset +8 (index 2) on that object.
        return ((int(**)(void))(g_pGlobalManager->field_0x7CC.vtable))[2]();
    }

    // Second attempt: interface GUID 0x197c1972
    hasInterface = (this->vtable[0x10])(0x197c1972, &interfacePtr);
    if (hasInterface && g_pGlobalManager != nullptr)
    {
        // Call a virtual function at offset 0x1E4 (index 0x79) on the global manager to get another pointer.
        void* someObject = (g_pGlobalManager->vtable[0x1E4])();
        if (someObject != nullptr)
        {
            // Check this object for interface 0xD80C71D2
            void* subInterface = nullptr;
            bool hasSub = (someObject->vtable[0x10])(0xD80C71D2, &subInterface);
            if (hasSub && subInterface != nullptr)
            {
                // Call virtual function at offset +8 (index 2) on the sub-interface.
                return ((int(**)(void))(subInterface.vtable))[2]();
            }
        }
    }

    return 0xFFFFFFFF;
}