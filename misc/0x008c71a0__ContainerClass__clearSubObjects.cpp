// FUNC_NAME: ContainerClass::clearSubObjects
// Function at 0x008c71a0: Releases all four sub-object pointers stored in a fixed array at this+0x14.
void __thiscall ContainerClass::clearSubObjects(void)
{
    // Array of 4 pointer-sized items at offset 0x14 in the class
    void** items = (void**)((char*)this + 0x14);
    for (int i = 0; i < 4; ++i)
    {
        releaseObject(items[i]); // FRE: release/deallocate the pointed object
    }
}