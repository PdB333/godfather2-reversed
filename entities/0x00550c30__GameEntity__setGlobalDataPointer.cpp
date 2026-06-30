// FUNC_NAME: GameEntity::setGlobalDataPointer
// Address: 0x00550c30
// Role: Initializes a member field at offset 0xAC with a global constant (DAT_00e2cd5c).
// This is likely a pointer to a manager or a configuration block.

// Global constant from data section
extern int gGlobalData; // DAT_00e2cd5c

void __fastcall GameEntity::setGlobalDataPointer(GameEntity* this)
{
    // Set the field at offset 0xAC to the global constant.
    // Offset 0xAC is likely a pointer to a global singleton or a state flag.
    *(int*)((char*)this + 0xAC) = gGlobalData;
}