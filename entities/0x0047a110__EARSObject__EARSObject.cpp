// FUNC_NAME: EARSObject::EARSObject
void* __thiscall EARSObject::EARSObject(byte bRegister)
{
    // Call base initialization (likely calls base class constructor or internal setup)
    this->initialize(); // calls FUN_0047a140

    // If the register flag (bit 0) is set, register this object with the global memory manager
    if ((bRegister & 1) != 0) {
        // Global manager pointer at 0x01223410, then offset +0x2d4 to get a vtable pointer
        // Virtual function at index 1 (second entry) is called with (this, 0)
        // This likely adds the object to a tracking list or performs post-construction registration
        (*(void(__thiscall*)(void*, int))(**(int**)((char*)0x01223410 + 0x2d4) + 4))(this, 0);
    }

    return this;
}