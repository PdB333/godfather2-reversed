// FUNC_NAME: constructMessageBuffer
void __cdecl constructMessageBuffer(void* param_1, void* param_2, void* param_3)
{
    char buffer[76]; // +0x0: unknown message/structure buffer (76 bytes)
    // Calls initialization helper (likely zeroes out some global state)
    FUN_00417560();
    // Calls the main construction routine with the buffer and parameters
    // Signature: FUN_005cf9a0(param_1, buffer, param_2, param_3)
    FUN_005cf9a0(param_1, buffer, param_2, param_3);
    return;
}