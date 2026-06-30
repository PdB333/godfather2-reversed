// FUN_00458c20: BaseSystem::shutdown
void __fastcall BaseSystem::shutdown(uint32_t* thisPtr)
{
    uint32_t** vtablePtr = reinterpret_cast<uint32_t**>(thisPtr);
    // Set vtable to derived class's vtable before destruction? (PTR_FUN_00e31aa4)
    *vtablePtr = &PTR_FUN_00e31aa4;

    uint32_t** childPtr = reinterpret_cast<uint32_t**>(thisPtr + 2); // offset +8
    for (int i = 0; i < 2; i++)
    {
        uint32_t* child = *childPtr;
        if (child != nullptr)
        {
            // Call virtual destructor or release function with argument 1
            (*(void(__thiscall*)(int))(*child))(1);
        }
        childPtr++;
    }

    // If global system initialized flag and local resource flag are set
    if (DAT_01143360 != 0 && thisPtr[1] != 0) // thisPtr[1] is offset +4
    {
        FUN_00c9eac0();
        FUN_00ca6640();
        FUN_00c9eae0();
        thisPtr[1] = 0; // Clear local resource flag
    }

    // Switch vtable to destructed/cleaned state (PTR_LAB_00e31aa8)
    *vtablePtr = &PTR_LAB_00e31aa8;

    // Clear global state flag
    DAT_012233fc = 0;
}