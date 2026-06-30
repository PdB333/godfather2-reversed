// FUNC_NAME: Entity::reset
void __thiscall Entity::reset(void)
{
    // Call some manager/logger with ID and some field
    // FUN_005dbc10 likely logs or manages something
    // +0x08: entity ID (16-bit)
    // +0x18: some pointer or value (32-bit)
    FUN_005dbc10(*(short *)(this + 0x08), *(int *)(this + 0x18));

    // Call a method in a global singleton (likely EntityManager) at offset 0x20
    // DAT_01223510 is probably a global pointer to a manager VTable
    (*(void (__thiscall **)(short))(*(int *)DAT_01223510 + 0x20))(*(short *)(this + 0x08));

    // Second call to the same function
    FUN_005dbc10(*(short *)(this + 0x08), *(int *)(this + 0x18));

    // If the "started" flag (bit 6 of byte at +0x10) is not set, perform additional cleanup
    if ((*(byte *)(this + 0x10) & 0x40) == 0) {
        FUN_005f1660(); // Likely a specific cleanup routine
    }

    // Zero out three state variables
    *(int *)(this + 0x24) = 0;
    *(int *)(this + 0x28) = 0;
    *(int *)(this + 0x2C) = 0;
}