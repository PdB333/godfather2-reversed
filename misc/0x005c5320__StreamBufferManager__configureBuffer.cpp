// FUNC_NAME: StreamBufferManager::configureBuffer
void StreamBufferManager::configureBuffer(int mode, int bufferSizeUnits)
{
    // mode: -1 = init/force reset, 0 = playback, 1 = record
    // bufferSizeUnits: number of 64-byte blocks (actual size = (bufferSizeUnits+1)*0x40)
    int cmdAlloc = s_commandAllocator; // DAT_01206880
    int iVar1;
    int *piVar2;
    uint *puVar3;
    undefined4 *puVar4;
    uint uVar5;
    undefined4 uVar6;

    if (mode == -1) {
        uVar5 = (bufferSizeUnits + 1) * 0x40;
        if ((s_currentMode != -1) || (s_bufferSize != uVar5)) {
            beginCommandList(); // FUN_005d8020
            iVar1 = s_commandAllocator;
            **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126bb8; // Command_Reset
            s_isStereo = (0 < bufferSizeUnits); // DAT_01205656
            piVar2 = (int *)(iVar1 + 0x14);
            *piVar2 = *piVar2 + 4; // advance write pointer
            piVar2 = (int *)(iVar1 + 0x14);
            *(undefined4 *)*piVar2 = 0;
            *piVar2 = *piVar2 + 4;
            puVar3 = (uint *)(s_commandAllocator + 0x14);
            **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126c08; // Command_SetFlag
            *puVar3 = *puVar3 + 4;
            *(undefined1 *)*puVar3 = 1; // flag value = 1 (enable?)
            *puVar3 = *puVar3 + 4 & 0xfffffffc;
            piVar2 = (int *)(s_commandAllocator + 0x14);
            s_currentMode = -1; // DAT_00f1765c
            s_bufferSize = uVar5; // DAT_0119da54
            if (bufferSizeUnits == 0) {
                *(undefined ***)*piVar2 = &PTR_LAB_01126c58; // Command_SetBuffer
                *piVar2 = *piVar2 + 4;
                puVar4 = (undefined4 *)(*piVar2 + 3U & 0xfffffffc);
                *piVar2 = (int)puVar4;
                *puVar4 = 1; // storage size? 1 byte? or flag?
                *piVar2 = *piVar2 + 4;
                *(undefined4 *)*piVar2 = 0; // address = 0 (null)
                *piVar2 = *piVar2 + 4;
                *(undefined4 *)*piVar2 = 0xc0; // some constant (192)
                *piVar2 = *piVar2 + 4;
            } else {
                *(undefined ***)*piVar2 = &PTR_LAB_01126c58; // Command_SetBuffer
                *piVar2 = *piVar2 + 4;
                puVar4 = (undefined4 *)(*piVar2 + 3U & 0xfffffffc);
                *piVar2 = (int)puVar4;
                *puVar4 = 4; // storage size? 4 bytes? or flag?
                *piVar2 = *piVar2 + 4;
                *(uint *)*piVar2 = uVar5; // buffer size
                *piVar2 = *piVar2 + 4;
                *(undefined4 *)*piVar2 = 0xc0;
                *piVar2 = *piVar2 + 4;
            }
            flushCommandList(); // FUN_005d56f0
            piVar2 = (int *)(s_commandAllocator + 0x14);
            **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126c80; // Command_Finalize
            *piVar2 = *piVar2 + 4;
            *(undefined4 *)*piVar2 = 0xc0;
            *piVar2 = *piVar2 + 4;
        }
    } else if (mode == 0) {
        if (s_currentMode != 0) {
            beginCommandList();
            piVar2 = (int *)(s_commandAllocator + 0x14);
            **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126bb8; // Command_Reset
            *piVar2 = *piVar2 + 4;
            *(undefined4 *)*piVar2 = 0xf;
            *piVar2 = *piVar2 + 4;
            if (s_isStereo == 0) { // DAT_01205656
                if ((s_flags & 2) != 0) { // DAT_01205684 bit 1? (0x02)
                    writeCommandSetBuffer(s_bufferAddress, 0x3f); // FUN_005d5880
                    flushCommandList();
                    writeCommandSomething(0x3f); // FUN_005d59b0
                    s_currentMode = 0;
                    return;
                }
                if ((s_flags & 4) == 0) { // DAT_01205684 bit 2? (0x04)
                    puVar3 = (uint *)(s_commandAllocator + 0x14);
                    **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126c08; // Command_SetFlag
                    *puVar3 = *puVar3 + 4;
                    *(undefined1 *)*puVar3 = 0; // flag value = 0 (disable)
                    *puVar3 = *puVar3 + 4 & 0xfffffffc;
                    s_currentMode = 0;
                    return;
                }
                uVar6 = 0x3f;
                uVar5 = s_bufferAddress;
            } else {
                if (s_currentMode == -1) {
                    configureBuffer(1, bufferSizeUnits - 1); // recursive call
                    writeCommandSomething(0xf); // FUN_005d5320
                }
                puVar3 = (uint *)(s_commandAllocator + 0x14);
                **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126c08; // Command_SetFlag
                *puVar3 = *puVar3 + 4;
                *(undefined1 *)*puVar3 = 1;
                *puVar3 = *puVar3 + 4 & 0xfffffffc;
                if ((s_flags & 2) != 0) {
                    writeCommandSetBuffer(s_bufferAddress | s_bufferSize, 0xff); // FUN_005d5880
                    flushCommandList();
                    writeCommandSomething(0x3f);
                    s_currentMode = 0;
                    return;
                }
                if ((s_flags & 4) == 0) {
                    writeCommandSetBuffer(s_bufferSize, 0xc0);
                    flushCommandList();
                    s_currentMode = 0;
                    return;
                }
                uVar6 = 0xff;
                uVar5 = s_bufferAddress | s_bufferSize;
            }
            writeCommandSetBuffer(uVar5, uVar6);
            flushCommandList();
            writeCommandSomething(0x3f);
            s_currentMode = 0;
            return;
        }
    } else if (mode == 1) {
        uVar5 = (bufferSizeUnits + 1) * 0x40;
        if ((s_currentMode != 1) || (s_bufferSize != uVar5)) {
            beginCommandList();
            s_currentMode = 1;
            s_bufferSize = uVar5;
            if (s_flag2 == 0) { // DAT_01205657
                initializeSomething(); // FUN_005d6dd0
                piVar2 = (int *)(s_commandAllocator + 0x14);
                **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126e38; // Command_RecordInit
                *piVar2 = *piVar2 + 4;
                *(undefined4 *)*piVar2 = 0x20;
                *piVar2 = *piVar2 + 4;
                s_flag2 = 1;
            }
            iVar1 = s_commandAllocator;
            **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126c08; // Command_SetFlag
            *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
            **(undefined1 **)(iVar1 + 0x14) = 1;
            *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) + 4 & 0xfffffffc;
            piVar2 = (int *)(s_commandAllocator + 0x14);
            **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126c80; // Command_Finalize
            *piVar2 = *piVar2 + 4;
            *(undefined4 *)*piVar2 = 0xc0;
            *piVar2 = *piVar2 + 4;
            if (bufferSizeUnits == 0) {
                writeCommandSetBuffer(0x40, 0xc0);
            } else {
                writeCommandSetBuffer(0x40, 0xc0);
            }
            flushCommandList();
            piVar2 = (int *)(s_commandAllocator + 0x14);
            **(undefined4 **)(s_commandAllocator + 0x14) = &PTR_LAB_01126bb8; // Command_Reset
            *piVar2 = *piVar2 + 4;
            *(undefined4 *)*piVar2 = 0;
            *piVar2 = *piVar2 + 4;
            s_isStereo = 1;
            return;
        }
    }
    return;
}
```