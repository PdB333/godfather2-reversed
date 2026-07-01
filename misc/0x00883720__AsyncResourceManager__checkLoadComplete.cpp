// FUNC_NAME: AsyncResourceManager::checkLoadComplete
bool AsyncResourceManager::checkLoadComplete(int param_1, int param_2, int* param_3)
{
    char cVar1;
    int iVar2;
    undefined1 auStack_14 [8];
    undefined1 local_c [12];
    int local_var; // stack0xffffffe4, likely a local variable

    iVar2 = getCurrentTime(); // FUN_00471610 - returns some timestamp or frame number
    // Call vtable method at offset 0xa4 on object pointed by param_3
    // This method likely reads data into local_c buffer from param_1+4 offset
    (**(code **)(*param_3 + 0xa4))(local_c, param_1 + 4);
    processEvents(); // FUN_0043b490 - yield or process pending events
    processEvents(); // called twice
    // Check if async load is complete; constants 0x40122 and 0x1ff0000 are flags/sizes
    cVar1 = checkAsyncStatus(iVar2 + 0x30, auStack_14, 0x40122, 0x1ff0000, &local_var, 2, 0, 0, 0);
    return cVar1 == '\0'; // returns true if status indicates completion
}