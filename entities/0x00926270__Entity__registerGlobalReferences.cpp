// FUNC_NAME: Entity::registerGlobalReferences
void __fastcall Entity::registerGlobalReferences(int thisPtr)
{
    // Clear or initialize global registration state
    FUN_005c1740();
    
    // Copy object fields at +0x50, +0x54, +0x58, +0x5c to global data arrays
    // These fields are likely pointers to sub-components (e.g., state machines, action handlers)
    FUN_005c01d0(&DAT_00d86468, thisPtr + 0x50, 1, 0, 0, 1);  // +0x50 -> global slot 0
    FUN_005c01d0(&DAT_00d878c4, thisPtr + 0x54, 1, 0, 0, 1);  // +0x54 -> global slot 1
    FUN_005c01d0(&DAT_00d878bc, thisPtr + 0x58, 1, 0, 0, 1);  // +0x58 -> global slot 2
    FUN_005c01d0(&DAT_00d878b4, thisPtr + 0x5c, 1, 0, 0, 1);  // +0x5c -> global slot 3
}