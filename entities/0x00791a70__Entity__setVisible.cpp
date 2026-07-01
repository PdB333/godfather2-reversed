// FUNC_NAME: Entity::setVisible
// Function address: 0x00791a70
// Sets a visibility/active flag and triggers appropriate actions based on state.
// Offsets: +0x5C flags, +0x9C state ID, +0xC8 type ID

void __thiscall Entity::setVisible(int thisPtr, char visible)
{
    uint flags = *(uint*)(thisPtr + 0x5C);
    int stateId = *(int*)(thisPtr + 0x9C);
    int typeId  = *(int*)(thisPtr + 200); // +0xC8

    if (visible == 0) {
        flags &= ~0x20000000; // Clear visibility flag (bit 29)
        *(uint*)(thisPtr + 0x5C) = flags;
    } else {
        flags |= 0x20000000; // Set visibility flag
        *(uint*)(thisPtr + 0x5C) = flags;

        // If state is active (not 0 and not 0x48) and type matches a specific hash
        if ((stateId != 0) && (stateId != 0x48) && (typeId == 0x637b907)) {
            int managerPtr = FUN_0043b870(DAT_01131018); // Get some manager singleton
            if (managerPtr != 0) {
                *(uint*)(managerPtr + 0x50) = 1; // Set some flag
            }
        }
    }

    // After visibility change, if state is active but type does not match the special hash
    if ((stateId != 0) && (stateId != 0x48) && (typeId != 0x637b907)) {
        FUN_00737940(5, 0); // Play sound/action
    }
}