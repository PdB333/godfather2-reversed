// FUNC_NAME: EARSObject::updateInternal
void __thiscall EARSObject::updateInternal(void)
{
    int *pLinkedObject; // Offset +0xc4: pointer to linked object or null
    int *pContainer;    // Temporarily computed from linked object

    // Check if we have a linked object
    if (*(int *)(this + 0xc4) == 0) {
        pContainer = 0;
    } else {
        // The linked object is at offset 0x48 from the container start (reversed)
        pContainer = (int *)(*(int *)(this + 0xc4) + -0x48);
    }

    // Store the container pointer at +0xb4
    *(int **)(this + 0xb4) = pContainer;

    if (pContainer != 0) {
        // Call a virtual method at vtable offset 0x58 (likely getData or getUID)
        // and store the result at +0x84
        *(int *)(this + 0x84) = (**(int (**)(void))(*(int *)pContainer + 0x58))();

        // Copy the sub-object at container+0x34 into this+0x30 (likely transform or state)
        FUN_0044b4e0(this + 0x30, pContainer + 0x34);
        return;
    }

    // No linked object: clean up and check flags
    FUN_0051d230(0); // Likely release/nullify some resource

    // Check a bitmask in an external object (this+0x10 is a pointer to some manager)
    if ((*(uint *)(*(int *)(this + 0x10) + 0x14) & 0x1000) != 0) {
        // If specific bit is not set in this+0xc, set it and call a process function
        if ((*(uint *)(this + 0xc) & 0x20000) == 0) {
            *(uint *)(this + 0xc) |= 0x20000;
            FUN_0051b120(); // Some global process (e.g., trigger event)
        }
        // Clear a different bit
        *(uint *)(this + 0xc) &= 0xfffbffff;
        return;
    }

    // Default path: call general update
    FUN_0051b2b0(this);
    return;
}