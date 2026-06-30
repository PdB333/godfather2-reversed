// FUNC_NAME: EntityManager::updateInteractableRangeChecks
void __thiscall EntityManager::updateInteractableRangeChecks(int thisPtr, int targetObj)
{
    float rangeThreshold;
    uint index;
    int arrayElement;
    int localStack[3]; // Actually a structure {int, ubyte, int} at locals - size 0xc?
    // local_c = int, local_8 = int, local_4 = ub? but the decompiler shows undefined4 local_c, int local_8, undefined1 local_4
    // Possibly a 12-byte struct with fields: 0:float, 4:??? , 8:int?

    // Set a processing flag on target (e.g., lock)
    *(uint *)(targetObj + 0x2658) |= 1;
    rangeThreshold = DAT_01205228; // Global range/threshold value

    index = 0;
    // Count of array elements at thisPtr+0xa28
    if (*(int *)(thisPtr + 0xa28) != 0) {
        // Array starts at thisPtr+0x28, each element size 0x28
        arrayElement = thisPtr + 0x28;
        do {
            // Check if element's distance (or value) at +0x24 is within threshold
            if (rangeThreshold <= *(float *)(arrayElement + 0x24)) {
                // Prepare local structure for interaction
                localStack[0] = DAT_0112ad8c; // Some constant (maybe an ID or parameter)
                localStack[2] = 0; // Actually local_4 = 0 (ubyte?) but set as zero
                // Set target's interaction source offset +0x3c as second parameter, or nullptr if targetObj==0
                if (targetObj == 0) {
                    // param_2+0x3c becomes 0
                    // local_8 = arrayElement
                    *(int *)(localStack+1) = 0; // Actually local_8 = iVar4? Wait: local_8 = iVar4 which is arrayElement. But decompiler shows local_8 = iVar4; after the if-else.
                } else {
                    // targetObj+0x3c is some structure pointer
                    // local_8 = arrayElement
                    *(int *)(localStack+1) = targetObj + 0x3c; // But wait: decompiler sets iVar2 = param_2+0x3c first, then local_8 = iVar4.
                }
                // Actually the decompiler code: if (param_2 == 0) { iVar2 = 0; } else { iVar2 = param_2 + 0x3c; } local_8 = iVar4;
                // So the third local (local_8) is always arrayElement. iVar2 is used as second param to callee.
                int secondParam = (targetObj != 0) ? (targetObj + 0x3c) : 0;
                // local_c is some constant, local_4 is 0, local_8 is arrayElement.
                // But the callee takes a pointer to these locals as first arg.
                FUN_00408bf0(localStack, secondParam, 0);
            }
            index++;
            arrayElement += 0x28;
        } while (index < *(uint *)(thisPtr + 0xa28));
    }
    // Clear processing flag
    *(uint *)(targetObj + 0x2658) &= 0xfffffffe;
    return;
}