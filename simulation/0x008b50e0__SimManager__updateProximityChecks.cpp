//FUNC_NAME: SimManager::updateProximityChecks
void __fastcall SimManager::updateProximityChecks(SimManager* thisPtr)
{
    int iVar1;
    int* piVar2;
    int* piVar3;
    int iVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    int iStack_20;
    int iStack_1c;
    undefined** local_18;
    int local_14;
    int local_10;
    undefined** ppuStack_c;
    int iStack_8;
    int iStack_4;

    // Check if global manager is active and this entity has the proximity flag set (bit 1 at +0x188)
    if ((*(int*)(DAT_01223484 + 8) != 0) && ((*(uint*)(thisPtr + 0x188) >> 1 & 1) != 0)) {
        // Get the entity's component or sub-object from offset +0x60
        local_10 = *(int*)(thisPtr + 0x60);
        local_18 = &PTR_FUN_00e35c28; // Iterator vtable for the object collection
        if ((local_10 == 0) || (*(int*)(local_10 + 8) == 0)) {
            local_10 = 0;
        }
        local_14 = 0;
        // Outer loop: iterate over all objects in the collection
        while ((local_14 != 0 || (local_10 != 0))) {
            iVar1 = (*(code*)*local_18)(); // Get current object from iterator
            if ((*(byte*)(iVar1 + 0x30) & 1) != 0) { // Check flag at +0x30 bit 0
                piVar2 = (int*)(*(code*)*local_18)(); // Get another reference? (same object?)
                FUN_008b3d60(&iStack_20, piVar2 + 2); // Extract object pointer from iterator
                if ((iStack_20 != 0) && (*(int*)(iStack_20 + 4) != 0)) {
                    ppuStack_c = &PTR_FUN_00e35c28; // Same iterator vtable
                    iStack_8 = local_14;
                    iStack_4 = local_10;
                    // Inner loop: compare current object with all others
                    do {
                        if ((iStack_8 == 0) && (iStack_4 == 0)) break;
                        iVar1 = (*(code*)*ppuStack_c)(); // Get next object
                        if ((*(byte*)(iVar1 + 0x30) & 1) != 0) {
                            piVar3 = (int*)(*(code*)*ppuStack_c)();
                            FUN_008b3d60(&iStack_1c, piVar3 + 2);
                            if (((iStack_1c != 0) && (*(int*)(iStack_1c + 4) != 0)) &&
                                // If the entity's flag at +0x188 bit 0 is clear, or the two objects are different
                                (((*(byte*)(thisPtr + 0x188) & 1) == 0 || (*piVar2 != *piVar3)))) {
                                iVar1 = FUN_008b4100(piVar3 + 2); // Get position of second object
                                iVar4 = FUN_008b4100(piVar2 + 2); // Get position of first object
                                // Compute squared distance between positions
                                fVar6 = *(float*)(iVar4 + 8) - *(float*)(iVar1 + 8);
                                fVar5 = *(float*)(iVar4 + 4) - *(float*)(iVar1 + 4);
                                fVar7 = *(float*)(iVar4 + 0xc) - *(float*)(iVar1 + 0xc);
                                if (fVar6 * fVar6 + fVar5 * fVar5 + fVar7 * fVar7 <= DAT_00d5d934) {
                                    // Objects are close: handle overlap
                                    FUN_004bc5b0(piVar3);
                                    FUN_004bc5b0(piVar2);
                                    FUN_008b4910(); // Overlap resolution
                                    (*(code*)ppuStack_c[1])(); // Advance inner iterator
                                    goto LAB_008b51b0; // Continue inner loop
                                }
                                // Objects are not close: handle separation
                                FUN_004bc5b0(piVar3);
                                FUN_004bc5b0(piVar2);
                                FUN_008b4b50(); // Separation handling
                            }
                        }
                        (*(code*)ppuStack_c[1])(); // Advance inner iterator
                    } while (true);
                }
            }
            (*(code*)local_18[1])(); // Advance outer iterator
        }
    }
    FUN_008ac6a0(); // Final update/cleanup
    return;
}