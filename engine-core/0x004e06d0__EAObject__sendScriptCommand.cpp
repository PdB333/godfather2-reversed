// FUNC_NAME: EAObject::sendScriptCommand
// Reconstructed from function at 0x004e06d0
// Sends a two-integer script command via global function pointer (DAT_01194538).
// command[0] = 2 (likely command ID), command[1] = 0 (parameter).
void EAObject::sendScriptCommand(void* this) // __thiscall
{
    int command[2];
    command[0] = 2; // +0x00: command type
    command[1] = 0; // +0x04: payload/parameter

    // Call through global function pointer (set during initialization)
    ((void (*)(void*, int*))(*DAT_01194538))(this, command);
}