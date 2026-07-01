// FUNC_NAME: Player::isActionAllowed
// Address: 0x00799a90
// Role: Determines if a player action is allowed based on various game state flags.

bool __thiscall Player::isActionAllowed(int thisPtr, char param_2)
{
    char cVar1;

    // Call virtual function at vtable+0x38 from object at offset 0x5f4.
    // If it returns non-zero, action is not allowed.
    cVar1 = (**(code **)(**(int **)(thisPtr + 0x5f4) + 0x38))();
    if (cVar1 == '\0') {
        // Else check two global functions (likely game state checks)
        cVar1 = FUN_00481660();  // Some game state flag?
        if (cVar1 == '\0') {
            cVar1 = FUN_00481640();  // Another flag?
            if (cVar1 == '\0') {
                return false;
            }
            // If flag at thisPtr+0x161 is set, action disallowed.
            if (*(char *)(thisPtr + 0x161) != '\0') {
                return false;
            }
        }
        // Check bit 23 of uint at offset 0x8e0.
        if ((*(uint *)(thisPtr + 0x8e0) >> 0x17 & 1) != 0) {
            return true;
        }
        // If param_2 is true, and first bit of byte at (offset 0x5f4)+0x18 is clear,
        // and FUN_00690150(0x5c) returns false, then allow action.
        if (((param_2 != '\0') && ((*(byte *)(*(int *)(thisPtr + 0x5f4) + 0x18) & 1) == 0)) &&
           (cVar1 = FUN_00690150(0x5c), cVar1 == '\0')) {
            return true;
        }
    }
    return false;
}