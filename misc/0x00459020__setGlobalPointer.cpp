// FUNC_NAME: setGlobalPointer
// Address: 0x00459020
// Simple setter for global pointer at 0x012053f4
// Called twice from FUN_0068d010 (likely initialization)
void setGlobalPointer(void* ptr)
{
    // Global variable at 0x012053f4 - likely a core engine interface pointer
    *(void**)0x012053f4 = ptr;
}