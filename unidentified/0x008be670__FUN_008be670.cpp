// FUNC_NAME: SomeManager::findSlotIndex
uint __thiscall SomeManager::findSlotIndex(int param_1, int param_2, float param_3, float param_4)
{
    int iVar1;
    int iVar2;
    uint uVar3;
    
    iVar1 = *(int *)(param_2 + 4); // count of slots
    uVar3 = 0;
    if (iVar1 != 0) {
        do {
            iVar2 = FUN_008c8170(); // likely slot index conversion or validation
            // Compare param_4 against value at offset 0x1b0 in param_1, using iVar2 as index, plus param_3
            if (param_4 < *(float *)(param_1 + 0x1b0 + iVar2 * 4) + param_3) {
                return uVar3;
            }
            uVar3 = uVar3 + 1;
        } while (uVar3 < *(uint *)(param_2 + 4)); // loop until all slots checked
    }
    return iVar1 - 1; // return last index if no slot found
}