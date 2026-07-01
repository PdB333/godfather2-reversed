// FUNC_NAME: SomeClass::setSomeFlagOrMode
void SomeClass::setSomeFlagOrMode(int param_1) // param_1 likely 'this' or a handle
{
    undefined4 *pVtable;
    undefined4 local_c; // +0x00: mode/type = 2
    undefined4 local_8; // +0x04: value/mask = 0x10
    undefined4 local_4; // +0x08: flags = 0

    pVtable = (undefined4 *)FUN_009c8f80(); // Get some singleton/manager vtable
    local_c = 2;   // Mode: e.g., kSetFlag, kSetMode
    local_8 = 0x10; // Value: e.g., flag bit 4 (0x10)
    local_4 = 0;    // Additional flags/options: none

    // Call a virtual method on the singleton, passing param_1 and the struct
    (**(code **)*pVtable)(param_1, &local_c);
    return;
}