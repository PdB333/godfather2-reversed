// FUNC_NAME: unknown::FUN_00926450
void FUN_00926450(void)
{
    // +0x0: local_c - likely a pointer or handle
    // +0x4: local_8 - zero-initialized
    // +0x8: local_4 - zero-initialized
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;
    
    // Load global data pointer (DAT_01130360) into local_c
    local_c = DAT_01130360;
    local_8 = 0;
    local_4 = 0;
    
    // Call function with pointer to local_c and 0 as parameters
    // Likely initializes or resets some structure
    FUN_00408a00(&local_c, 0);
    
    // Indirect call through vtable at offset 0x28 of object pointed by DAT_01129a74
    // This is a virtual method call (likely a member function)
    (**(code **)(*DAT_01129a74 + 0x28))();
    
    return;
}