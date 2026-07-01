//FUNC_NAME: Player::playStateSound
void __fastcall Player::playStateSound(int *thisPtr)
{
    byte bVar1;
    int iVar2;
    byte bVar3;
    int iVar4;
    int iVar5;
    char unaff_BL;
    undefined4 uVar6;

    // Get character pointer at offset 0x50
    int *character = (int *)thisPtr[0x14];

    // Read state fields from character
    iVar2 = *(int *)(character + 0x1010);      // +0x1010: some state index
    bVar1 = *(byte *)(character + 0x1b8c);     // +0x1b8c: state type (0-4)

    // Debug/log call
    FUN_007f63e0(6);

    // Call virtual function at offset 0x290 on character (likely setState or similar)
    (**(code **)(*(int *)character + 0x290))(0, 4);

    // Get global game manager singleton
    int *gameManager = *(int **)(DAT_012233a0 + 4);
    if (gameManager == 0) {
        iVar5 = 0;
    } else {
        iVar5 = (int)gameManager - 0x1f30;   // Subtract offset to get player object
    }

    // Get another pointer from character at +0xffc, subtract 0x48
    if (*(int *)(character + 0xffc) == 0) {
        iVar4 = 0;
    } else {
        iVar4 = *(int *)(character + 0xffc) - 0x48;
    }

    // Check if this character is the player
    if (iVar4 == iVar5) {
        bVar3 = FUN_007f95d0();   // Returns 0 or 1 (maybe player-specific state)
    } else {
        bVar3 = 0;
    }

    // If state index is non-zero
    if (iVar2 != 0) {
        // Check condition: byte at this+0x55 == 0, iVar2 >= 0, bVar1 < 2
        if ((*(char *)((int)thisPtr + 0x55) == 0) && (-1 < iVar2) && (bVar1 < 2)) {
            // Compute index into sound table (2D: bVar1 rows, iVar2 columns, each entry 4 bytes)
            int soundIndex = ((uint)bVar3 + ((char)bVar1 * 0x5b + iVar2) * 2) * 4;
            uint soundId = *(uint *)(&DAT_00d725f0 + soundIndex);
            // Play sound via virtual function at offset 0x2c on this
            (**(code **)(*thisPtr + 0x2c))(soundId, 1, 1, 0, 0x3f800000, 0x3f800000);
        }
        return;
    }

    // iVar2 == 0: handle based on bVar1
    if (bVar1 == 0) {
        if (bVar3 == 0) {
            (**(code **)(*thisPtr + 0x2c))(0xfc922916, 1, 1, 0, 0x3f800000, 0x3f800000);
        } else if (bVar3 == 1) {
            (**(code **)(*thisPtr + 0x2c))(0x8b863453, 1, 1, 0, 0x3f800000, 0x3f800000);
        }
        return;
    }

    if ((bVar1 == 1) || (bVar1 == 4)) {
        if (bVar3 == 0) {
            uVar6 = 0xe1e25be9;
        } else if (bVar3 == 1) {
            uVar6 = 0x60cdfaa6;
        } else {
            goto LAB_0080c92c;
        }
    } else if ((bVar1 == 2) || (bVar1 == 3)) {
        uVar6 = 0x9d4e8047;
    } else {
        return;
    }

    (**(code **)(*thisPtr + 0x2c))(uVar6, 1, 1, 0, 0x3f800000, 0x3f800000);

LAB_0080c92c:
    // Call virtual function at offset 0x234 on character (likely cleanup/end)
    (**(code **)(*(int *)character + 0x234))(1, 1);
    return;
}