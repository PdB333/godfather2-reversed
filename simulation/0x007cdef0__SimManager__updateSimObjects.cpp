// FUNC_NAME: SimManager::updateSimObjects
void __thiscall SimManager::updateSimObjects(void)
{
    int* piVar1;
    int iVar2;
    undefined4* puVar3;

    // Set flag at +0x1d0 to indicate update in progress (bit 0x200)
    *(uint*)(this + 0x1d0) |= 0x200;

    // Call global update function with parameters (0, 1) - likely frame counter or something
    FUN_007ab9a0(0, 1);

    // Get list of objects of type 9 (e.g., SimObjectType::NPC or similar)
    puVar3 = (undefined4*)FUN_0043c2c0(9);
    for (piVar1 = (int*)*puVar3; piVar1 != (int*)0x0; piVar1 = (int*)piVar1[1]) {
        iVar2 = *piVar1;
        if (iVar2 != 0) {
            // Process the object (type 9)
            FUN_0043c5b0(iVar2, 9);
            // Global update function
            FUN_0070b4a0();
            // Update sub-object at offset +0x3c (likely a component or data block)
            FUN_004088c0(iVar2 + 0x3c);
        }
    }
    return;
}