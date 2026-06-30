// FUNC_NAME: SomeManager::processCommand
void __thiscall SomeManager::processCommand(int param_2, undefined4 param_3) {
    int iVar3 = -1;
    // Check if a member pointer (likely a manager or state) is non-null
    if (*(int *)(this + 0x18) != 0) {
        iVar3 = FUN_00650f30(); // Returns an identifier or handle
    }
    undefined4 uVar1 = param_3;
    char cVar2 = FUN_0064bb50(iVar3 != -1); // Likely checks/validates result
    if (cVar2 != '\0') {
        param_2 = iVar3;
        FUN_0064b810(10, &param_2); // Possibly debug/log with id 10
        // Call a function pointer from an interface (vtable at this+0x14)
        (**(code **)(**(int **)(this + 0x14) + 8))(uVar1);
        // Update some flag state – bitwise clear/set operation
        FUN_0064bb50(*(uint *)(*(int *)(this + 0x18) + 0x30) >> 1 & 0xffffff01);
    }
    return;
}