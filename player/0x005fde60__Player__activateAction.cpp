// FUNC_NAME: Player::activateAction
// Address: 0x005fde60
// Purpose: Sets a flag at +0xBC to 1 and calls an underlying action function with three parameters and a global constant.
// The three parameters (data[0], data[1], data[2]) likely represent coordinates, IDs, or state data.
// Global DAT_00e2b1a4 is probably a timestamp or constant used by the engine.

void __thiscall Player::activateAction(uint32_t *data)
{
    // +0xBC: activation/state flag (1 = active)
    *(uint32_t *)((uint8_t *)this + 0xBC) = 1;

    // Call helper with three data values and a global
    FUN_00414aa0(data[0], data[1], data[2], DAT_00e2b1a4);
}