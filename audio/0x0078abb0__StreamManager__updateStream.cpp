// FUNC_NAME: StreamManager::updateStream
void __fastcall StreamManager::updateStream(void* thisPtr)
{
    int* piVar1;
    int iVar2;
    undefined4 uVar3;
    float fVar4;
    char local_5[5];

    // Release two global audio buffers if they exist
    if (DAT_0112afd8 != 0) {
        FUN_00408900(thisPtr, &DAT_0112afd8, 0x8000);
    }
    if (DAT_0112afe0 != 0) {
        FUN_00408900(thisPtr, &DAT_0112afe0, 0x8000);
    }

    // Check if a specific sound instance has a flag set (bit 8 at offset 0x1f54)
    // and if the associated entity is valid and has a certain state (bit 0x19 at offset 0x34)
    if ((((*(uint*)(*(int*)((char*)thisPtr + 0x5c) + 0x1f54) >> 8 & 1) != 0) &&
         (iVar2 = FUN_006b07e0(*(undefined4*)(*(int*)((char*)thisPtr + 0x5c) + 0x2134)), iVar2 != 0)) &&
        ((*(uint*)(*(int*)(iVar2 + 0x180) + 0x34) >> 0x19 & 1) != 0))
    {
        // Smooth interpolation of two float values (e.g., volume or pan)
        fVar4 = (*(float*)((char*)thisPtr + 0x58) - *(float*)((char*)thisPtr + 0x54)) * DAT_00d5c454;
        *(float*)((char*)thisPtr + 0x54) = *(float*)((char*)thisPtr + 0x54) + fVar4;
        *(float*)((char*)thisPtr + 0x58) = *(float*)((char*)thisPtr + 0x58) - fVar4;
    }

    // Manage a list of active stream objects (pointers at +0x24, +0x28, +0x2c, +0x30)
    if (((*(int*)((char*)thisPtr + 0x24) != 0) || (*(int*)((char*)thisPtr + 0x28) != 0)) ||
        ((*(int*)((char*)thisPtr + 0x2c) != 0 || (*(int*)((char*)thisPtr + 0x30) != 0))))
    {
        local_5[0] = 0;
        iVar2 = FUN_00448100((char*)thisPtr + 0x24, local_5);
        piVar1 = (int*)((char*)thisPtr + 0x1c);
        if (iVar2 == 0) {
            iVar2 = 0;
        }
        else {
            iVar2 = iVar2 + 0x3c;
        }
        // Replace the head of the linked list if the new node differs
        if (*piVar1 != iVar2) {
            if (*piVar1 != 0) {
                FUN_004daf90(piVar1); // Remove old head from list
            }
            *piVar1 = iVar2;
            if (iVar2 != 0) {
                *(undefined4*)((char*)thisPtr + 0x20) = *(undefined4*)(iVar2 + 4);
                *(int**)(iVar2 + 4) = piVar1;
            }
        }
    }

    // Update a field based on a global singleton
    if (*(int*)((char*)thisPtr + 0xc) == 0) {
        uVar3 = 0;
    }
    else {
        uVar3 = FUN_0043b870(DAT_01131018);
    }
    *(undefined4*)((char*)thisPtr + 0x60) = uVar3;

    // Process a sub-object (e.g., a timer or state machine)
    FUN_009aefd0((char*)thisPtr + 0x10, 0x8000);

    // Copy a value to two output fields
    *(undefined4*)((char*)thisPtr + 0x40) = *(undefined4*)((char*)thisPtr + 0x4c);
    *(undefined4*)((char*)thisPtr + 0x50) = *(undefined4*)((char*)thisPtr + 0x4c);

    return;
}