//FUNC_NAME: SomeManager::updateCurrentItem
void __fastcall SomeManager::updateCurrentItem(int thisPtr)
{
    int* piVar1;
    int uVar2;
    int iVar3;
    int* piVar4;
    int local_2c;
    int local_28;
    int local_24;
    int local_20;
    int local_1c;
    int local_18;
    int local_14;

    // Initialize a 4-component vector (likely position/orientation)
    FUN_008fe280(&local_2c);
    local_20 = local_2c;
    local_1c = local_28;
    local_18 = local_24;
    local_14 = _DAT_00d5780c; // Global constant (e.g., 1.0f or 0.0f)

    // Set the transform on the object at offset 0xd8
    FUN_00949ca0(*(int*)(thisPtr + 0xd8), &local_20);

    // Get the current item ID from a singleton
    uVar2 = FUN_008fe1e0();
    iVar3 = FUN_006b0ee0(uVar2);
    if (iVar3 == 0) {
        iVar3 = 0;
    } else {
        iVar3 = *(int*)(iVar3 + 0x48); // Extract handle from object
    }

    piVar1 = (int*)(thisPtr + 0xe0); // Pointer to stored handle
    if (*(int*)(thisPtr + 0xe0) != iVar3) {
        // Clear the local vector
        local_2c = 0;
        local_28 = 0;
        local_24 = 0;

        // Update stored handle
        *piVar1 = iVar3;

        // Reference counting / pointer management
        piVar4 = (int*)FUN_006b4d50(piVar1);
        if (piVar4 != (int*)0x0) {
            *piVar4 = *piVar1;
        }

        // Notify the object at offset 0xd8 about the change
        FUN_0094b510(*(int*)(thisPtr + 0xd8), &local_2c);
        if (local_2c != 0) {
            FUN_009c8f10(local_2c); // Release reference
        }
    }
    return;
}