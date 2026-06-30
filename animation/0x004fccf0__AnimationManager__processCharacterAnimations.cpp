// FUNC_NAME: AnimationManager::processCharacterAnimations
void __thiscall AnimationManager::processCharacterAnimations(int thisPtr, int cameraMatrix)
{
    int iVar1;
    int iVar2;
    int charIndex;
    uint charCount;
    undefined4 local_b0;
    undefined4 uStack_ac;
    undefined4 uStack_a8;
    undefined4 uStack_a4;
    undefined4 local_9c[3];
    undefined4 local_90;
    undefined4 uStack_8c;
    undefined4 uStack_88;
    undefined4 uStack_84;
    undefined4 local_80;
    undefined4 uStack_7c;
    undefined4 uStack_78;
    undefined4 uStack_74;
    undefined4 local_70;
    undefined4 uStack_6c;
    undefined4 uStack_68;
    undefined4 uStack_64;
    undefined4 local_60;
    undefined4 uStack_5c;
    undefined4 uStack_58;
    undefined4 uStack_54;

    // Copy 16 floats from cameraMatrix+0x40 to local stack (4x4 matrix?)
    local_90 = *(undefined4 *)(cameraMatrix + 0x40);
    uStack_8c = *(undefined4 *)(cameraMatrix + 0x44);
    uStack_88 = *(undefined4 *)(cameraMatrix + 0x48);
    uStack_84 = *(undefined4 *)(cameraMatrix + 0x4c);
    local_80 = *(undefined4 *)(cameraMatrix + 0x50);
    uStack_7c = *(undefined4 *)(cameraMatrix + 0x54);
    uStack_78 = *(undefined4 *)(cameraMatrix + 0x58);
    uStack_74 = *(undefined4 *)(cameraMatrix + 0x5c);
    local_70 = *(undefined4 *)(cameraMatrix + 0x60);
    uStack_6c = *(undefined4 *)(cameraMatrix + 100);
    uStack_68 = *(undefined4 *)(cameraMatrix + 0x68);
    uStack_64 = *(undefined4 *)(cameraMatrix + 0x6c);
    local_60 = *(undefined4 *)(cameraMatrix + 0x70);
    uStack_5c = *(undefined4 *)(cameraMatrix + 0x74);
    uStack_58 = *(undefined4 *)(cameraMatrix + 0x78);
    uStack_54 = *(undefined4 *)(cameraMatrix + 0x7c);

    charCount = 0;
    if (*(int *)(thisPtr + 0x20) != 0) {
        charIndex = 0;
        do {
            // Pointer to current character structure (size 0x1b0)
            iVar2 = *(int *)(thisPtr + 0x1c) + charIndex;

            // Initialize some animation state (maybe matrix stack)
            FUN_005334b0(local_9c, (-(uint)(*(int *)(thisPtr + 0x14) != 0) & 0xffffffc0) + 0x40);
            FUN_00534ff0(0);
            FUN_00417560();
            FUN_00535220();

            // Copy 4 floats from pointer at thisPtr+0x10 to global render state
            iVar1 = *(int *)(thisPtr + 0x10);
            _DAT_01219b40 = *(undefined4 *)(iVar1 + 0x74);
            _DAT_01219b44 = *(undefined4 *)(iVar1 + 0x78);
            _DAT_01219b48 = *(undefined4 *)(iVar1 + 0x7c);
            // Copy from character structure at offset 0x190 (400) to global
            _DAT_01219b4c = *(undefined4 *)(iVar2 + 400);

            local_b0 = _DAT_01219b40;
            uStack_ac = _DAT_01219b44;
            uStack_a8 = _DAT_01219b48;
            uStack_a4 = _DAT_01219b4c;

            // Debug/editor check: if a specific global pointer matches, call a debug render function
            if ((DAT_012058e8 == &DAT_01219a70) &&
                (*(int *)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30) != 0)) {
                FUN_0060add0(DAT_01219a80, *(int *)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30), &local_b0);
            }

            // Clamp LOD/quality thresholds
            if (DAT_012058d0 < 0xe) {
                DAT_012058d0 = 0xe;
            }
            if (0xe < DAT_00f15988) {
                DAT_00f15988 = 0xe;
            }

            iVar1 = 0;
            _DAT_011f3a10 = 0;
            if (DAT_012058d0 < 0x1b) {
                DAT_012058d0 = 0x1b;
            }
            if (0x1a < DAT_00f15988) {
                DAT_00f15988 = 0x1b;
            }
            _DAT_011f3a44 = 1;
            FUN_004ec7a0();

            local_9c[0] = DAT_00e2b1a4;
            FUN_004eccc0(8);

            // Process animation passes based on byte at character+0x1ad
            if (*(byte *)(iVar2 + 0x1ad) != 1 && -1 < (int)(*(byte *)(iVar2 + 0x1ad) - 1)) {
                do {
                    FUN_004fca40(thisPtr, local_9c);
                    iVar1 = iVar1 + 1;
                } while (iVar1 < (int)(*(byte *)(iVar2 + 0x1ad) - 1));
            }

            FUN_00533720(local_9c);

            charIndex += 0x1b0; // stride of character structure
            charCount++;
        } while (charCount < *(uint *)(thisPtr + 0x20));
    }

    if (*(int *)(thisPtr + 0x20) != 0) {
        *(undefined4 *)(thisPtr + 0x20) = 0; // reset count
    }
    return;
}