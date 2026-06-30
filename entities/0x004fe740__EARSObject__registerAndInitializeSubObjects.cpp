// FUNC_NAME: EARSObject::registerAndInitializeSubObjects
// Address: 0x004fe740
// Role: Registers the object in a global vtable-based list and processes a fixed number of sub-objects.
// Offsets used:
//   +0x00: vtable pointer
//   +0x3C: int m_subObjectCount (number of iterations for sub-object processing)
// Global: DAT_01206880 + 0x14 points to a growing list buffer (used as a placement arena)

void __thiscall EARSObject::registerAndInitializeSubObjects(void)
{
    // Global list insertion point (buffer pointer inside a manager)
    int* pInsertionPoint = (int*)(DAT_01206880 + 0x14);

    // Write vtable pointer for this object type into the list
    *(void***)*pInsertionPoint = &PTR_LAB_01124ee0;  // vtable address
    *pInsertionPoint += 4;  // advance past vtable slot

    // Store this object's pointer after the vtable
    *(int*)*pInsertionPoint = (int)this;
    *pInsertionPoint += 4;  // advance to next insertion slot

    // Process each sub-object (e.g., child nodes, components)
    int i = 0;
    if (0 < *(int*)((int)this + 0x3C))  // m_subObjectCount
    {
        do {
            FUN_004fe5d0(this);  // process one sub-object (likely reads m_subObjectCount)
            i++;
        } while (i < *(int*)((int)this + 0x3C));
    }
}