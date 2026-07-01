// FUNC_NAME: callCoreUpdate
void callCoreUpdate(void)
{
    // Forward to the core engine update routine at 0x004d3d90.
    // This function is invoked from many game update hooks (e.g., FUN_009341d0, FUN_00934410, etc.).
    FUN_004d3d90();
    return;
}