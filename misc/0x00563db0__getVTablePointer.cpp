//FUNC_NAME: getVTablePointer
// Function at 0x00563db0 returns address of a static vtable pointer.
// This is a common pattern in the EARS engine for accessing virtual function tables.

extern void* PTR_FUN_00e3a4b4; // Static vtable pointer

void** getVTablePointer(void)
{
    return &PTR_FUN_00e3a4b4;
}