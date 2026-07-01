// FUNC_NAME: UIManager::deleteAllUIProperties
void UIManager::deleteAllUIProperties(void)
{
    int iVar1;
    int iVar2;
    undefined4 uVar3;
    undefined2 *puVar4;
    undefined1 *puVar5;
    int loopIndex;
    undefined1 *local_20;
    undefined4 local_1c;
    undefined4 local_18;
    code *local_14;
    undefined2 *local_10[3];
    code *local_4;
    
    // Allocate or get the UI manager singleton (size 0xF0)
    iVar2 = allocateOrGetManager(0xf0);
    if (iVar2 == 0) {
        iVar2 = 0;
    }
    else {
        iVar2 = initializeManager(0);
    }
    // Clear a flag at offset +0xC
    *(undefined4 *)(iVar2 + 0xc) = 0;
    // Delete the "$ui_pro_delete" property twice (maybe for different contexts)
    uiPropertyDelete("$ui_pro_delete");
    uiPropertyDelete("$ui_pro_delete");
    // Clear all UI properties
    clearUIProperties(0);
    // Set a vtable or function pointer at offset +0x14
    *(undefined1 **)(iVar2 + 0x14) = &LAB_00933210;
    
    loopIndex = 0;
    // Iterate over an array of UI elements (stride 0x504)
    if (*(short *)(DAT_0113056c + 4) != 0) {
        iVar2 = 0;
        do {
            iVar1 = DAT_0113055c + iVar2;
            // Release references or destroy the element
            uVar3 = someReleaseFunction(iVar1);
            anotherReleaseFunction(iVar1, uVar3);
            // Initialize local array (maybe to null)
            initLocalArray(local_10);
            local_20 = (undefined1 *)0x0;
            local_1c = 0;
            local_18 = 0;
            local_14 = (code *)0x0;
            puVar4 = local_10[0];
            if (local_10[0] == (undefined2 *)0x0) {
                puVar4 = &DAT_00e2df14;
            }
            // Get a string or object from the pointer
            getStringFromPointer(puVar4, &local_20);
            puVar5 = local_20;
            if (local_20 == (undefined1 *)0x0) {
                puVar5 = &DAT_0120546e;
            }
            // Apply the string to the UI (e.g., set text or delete)
            uiSetTextOrDelete(puVar5, 0, 0);
            // Call destructor if object exists
            if (local_20 != (undefined1 *)0x0) {
                (*local_14)(local_20);
            }
            // Free the local array if allocated
            if (local_10[0] != (undefined2 *)0x0) {
                (*local_4)(local_10[0]);
            }
            loopIndex = loopIndex + 1;
            iVar2 = iVar2 + 0x504;
        } while (loopIndex < (int)(uint)*(ushort *)(DAT_0113056c + 4));
    }
    // Final cleanup
    finalCleanup();
    return;
}