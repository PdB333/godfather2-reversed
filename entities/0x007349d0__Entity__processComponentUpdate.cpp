// FUNC_NAME: Entity::processComponentUpdate
// Address: 0x007349d0
// This function checks a bitflag (bit 10 of field at +0x8E0) and if active, calls two virtual methods (vtable offsets 0x6C and 0x7C) on a component stored at +0x74C, which is adjusted by -0x48 to obtain the base object.
void __fastcall Entity::processComponentUpdate(Entity* this)  // param_1 = this
{
    // Read bitfield at this+0x8E0 (likely flags for update/activity)
    uint flags = *(uint*)((char*)this + 0x8E0);

    // Call a global helper (unknown purpose, maybe frame tick or audio update)
    someGlobalTickFunction();  // FUN_00800830

    // Check if bit 10 is set and if the component pointer is valid (non-null and not a sentinel 0x48)
    if ( ((flags >> 10) & 1) &&
         (*(int*)((char*)this + 0x74C) != 0) &&
         (*(int*)((char*)this + 0x74C) != 0x48) )
    {
        // Retrieve the component pointer from this+0x74C
        int* componentPtr = *(int**)((char*)this + 0x74C);

        // Adjust by -0x48 to get the actual base object (multiple inheritance offset)
        int* baseObj;
        if (componentPtr == nullptr) {
            baseObj = nullptr;
        } else {
            baseObj = (int*)((char*)componentPtr - 0x48);
        }

        // Call virtual function at vtable index 0x6C (e.g., some update method)
        (*(void (__thiscall**)(int*))(*baseObj + 0x6C))(baseObj);

        // Call virtual function at vtable index 0x7C (e.g., another update or post-process)
        (*(void (__thiscall**)(int*))(*baseObj + 0x7C))(baseObj);
    }
}