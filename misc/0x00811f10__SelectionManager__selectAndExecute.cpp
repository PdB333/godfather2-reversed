// FUNC_NAME: SelectionManager::selectAndExecute
void __thiscall SelectionManager::selectAndExecute(int this, int param_2)
{
    int iVar1;
    char cVar2;
    uint uVar3;
    int uVar4;
    int iVar5;
    int validCount;
    int indexInList;
    int listBuffer; // used for temporary list building
    
    int totalEntries = DAT_0112dac8; // +0x0? count of elements
    iVar5 = 0;
    validCount = 0;
    indexInList = 0;
    listBuffer = 0;
    
    if (0 < totalEntries) {
        do {
            // Call virtual function at +0x1c (likely "canPlay" / "isValid")
            cVar2 = (**(code **)(*(int *)(&DAT_0112da48)[iVar5] + 0x1c))(this, param_2);
            if (cVar2 != '\0') {
                if (validCount == 0) {
                    // Initialize selection process
                    FUN_00811420(1); // "beginSelection" or "resetActiveList"
                    indexInList = listBuffer; // listBuffer is 0 initially
                }
                validCount = indexInList + 1;
                listBuffer = validCount;
                
                // Store pointer into a temporary list (address base is missing, possibly global or stack? decompiler artifact)
                if ((int *)(indexInList * 4) != (int *)0x0) {
                    *(int *)(indexInList * 4) = (int)(&DAT_0112da48)[iVar5];
                }
            }
            iVar5 = iVar5 + 1;
        } while (iVar5 < totalEntries);
        
        if (0 < validCount) {
            // Weighted random selection from valid entries
            uVar3 = DAT_010c2678 & DAT_012054b4; // pseudorandom index into weight table
            DAT_012054b4 = DAT_012054b4 + 1;     // increment random seed counter
            iVar1 = *(int *)((int)((float)validCount * *(float *)(&DAT_010c2680 + uVar3 * 4)) * 4); // get weighted index (rounded, multiplied by 4 for pointer offset)
            
            uVar4 = FUN_00811920(this, iVar1); // "getSelectedAnimation" or similar
            FUN_0079e3c0(iVar1 + 0x60, uVar4, iVar1 + 0xa0, 0); // apply animation parameters (offset 0x60 and 0xa0)
            FUN_009c8f10(0); // finalize or reset
        }
    }
    return;
}