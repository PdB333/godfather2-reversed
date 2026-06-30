// FUNC_NAME: unknownInitializationFunction
void __thiscall unknownInit(void)
{
    // 16-byte buffer (local_30)
    char buffer16[16];
    // 28-byte buffer (local_20)
    char buffer28[28];

    // Build or fill the two buffers (likely a struct split across them)
    FUN_00535640(buffer28, buffer16);

    // Update global / singleton state
    FUN_00534ea0();

    // Finalize using the 16-byte buffer
    FUN_00534e20(buffer16);
}