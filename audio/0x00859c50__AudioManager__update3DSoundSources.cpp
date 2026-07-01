// FUNC_NAME: AudioManager::update3DSoundSources
void __fastcall AudioManager::update3DSoundSources(int thisPtr)
{
    short *pSoundSlot;
    int soundIndex;
    int local_a4;
    int iStack_ac;
    int iStack_a0;
    int iStack_9c;
    int iStack_98;
    undefined4 auStack_94 [12];
    int iStack_64;
    int iStack_60;
    int iStack_5c;
    undefined1 auStack_54 [4];
    undefined1 auStack_50 [76];
    
    pSoundSlot = (short *)(thisPtr + 0x168); // +0x168: sound slot array (3 slots, each 16 bytes)
    local_a4 = 3;
    do {
        if (((*pSoundSlot != 0) && // slot active
            (*(uint *)(thisPtr + 0x1b8) < (uint)(DAT_01205224 - *(int *)(pSoundSlot + 2)))) && // time check
           ((*(int *)(thisPtr + 0x198) != 0 || // listener position valid
            (((*(int *)(thisPtr + 0x19c) != 0 || (*(int *)(thisPtr + 0x1a0) != 0)) ||
             (*(int *)(thisPtr + 0x1a4) != 0)))))) {
            float10 fVar7 = (float10)(**(code **)(**(int **)(thisPtr + 0xf8) + 0x1b0))(); // get random float
            if (fVar7 < (float10)*(float *)(thisPtr + 0x1bc)) { // probability check
                if (*(int *)(pSoundSlot + 4) != 0) {
                    FUN_004df650(); // stop sound
                }
            }
            else if (*(int *)(pSoundSlot + 4) == 0) { // sound not playing
                int *pSoundData = (int *)(**(code **)(**(int **)(pSoundSlot + 6) + 0x2c))(*pSoundSlot); // get sound data
                iStack_a0 = *pSoundData;
                iStack_9c = pSoundData[1];
                iStack_98 = pSoundData[2];
                undefined4 *pMatrix = (undefined4 *)FUN_00471610(); // get identity matrix
                undefined4 *pDest = auStack_94;
                for (int i = 0x10; i != 0; i--) {
                    *pDest = *pMatrix;
                    pMatrix++;
                    pDest++;
                }
                iStack_64 = iStack_a0;
                iStack_60 = iStack_9c;
                iStack_5c = iStack_98;
                FUN_0044b4e0(auStack_54, auStack_94); // transform matrix
                undefined4 uVar3 = (**(code **)(**(int **)(iStack_ac + 0xf8) + 0x58))(0, 0, 0xffffffff, 0); // get sound handle
                uVar3 = FUN_004df330(&iStack_a0, iStack_ac + 0x198, auStack_50, uVar3); // play 3D sound
                FUN_00414db0(uVar3); // release handle
                thisPtr = iStack_ac;
                if (iStack_a0 != 0) {
                    *(undefined4 *)(iStack_a0 + 8) = 0;
                    iStack_a0 = 0;
                }
            }
        }
        pSoundSlot = pSoundSlot + 8; // advance to next slot (8 shorts = 16 bytes)
        local_a4 = local_a4 + -1;
    } while (local_a4 != 0);
    return;
}