// FUNC_NAME: RenderManager::updateViewMatrices
void RenderManager::updateViewMatrices(void)
{
    // Copy source matrices to working buffers (first set of 16 floats each)
    // Source: 0x011f6a30 -> Destination: 0x011f67b0
    _DAT_011f67b0 = _DAT_011f6a30;
    uRam011f67b4 = uRam011f6a34;
    uRam011f67b8 = uRam011f6a38;
    uRam011f67bc = uRam011f6a3c;
    _DAT_011f67c0 = _DAT_011f6a40;
    uRam011f67c4 = DAT_011f6a44;
    uRam011f67c8 = uRam011f6a48;
    uRam011f67cc = uRam011f6a4c;
    _DAT_011f67d0 = _DAT_011f6a50;
    uRam011f67d4 = uRam011f6a54;
    uRam011f67d8 = DAT_011f6a58;
    uRam011f67dc = DAT_011f6a5c;
    _DAT_011f67e0 = _DAT_011f6a60;
    uRam011f67e4 = uRam011f6a64;
    uRam011f67e8 = DAT_011f6a68;
    uRam011f67ec = DAT_011f6a6c;

    // If camera pointer exists and has valid view matrix (offset +0x3c)
    if ((DAT_012058e8 != 0) && (*(int *)(DAT_012058e8 + 0x3c) != 0))
    {
        // Transform the first matrix using camera data: position/offset at +0x10, view matrix at +0x3c, store to g_workingMatrix0
        FUN_0060b020(*(undefined4 *)(DAT_012058e8 + 0x10), *(int *)(DAT_012058e8 + 0x3c), &DAT_011f67b0);
    }

    // Copy second set of 16 floats (projection matrix)
    // Source: 0x011f6af0 -> Destination: 0x011f6830
    _DAT_011f6830 = _DAT_011f6af0;
    uRam011f6834 = uRam011f6af4;
    uRam011f6838 = uRam011f6af8;
    uRam011f683c = uRam011f6afc;
    _DAT_011f6840 = _DAT_011f6b00;
    uRam011f6844 = uRam011f6b04;
    uRam011f6848 = uRam011f6b08;
    uRam011f684c = uRam011f6b0c;
    _DAT_011f6850 = _DAT_011f6b10;
    uRam011f6854 = uRam011f6b14;
    uRam011f6858 = uRam011f6b18;
    uRam011f685c = uRam011f6b1c;
    _DAT_011f6860 = _DAT_011f6b20;
    uRam011f6864 = uRam011f6b24;
    uRam011f6868 = uRam011f6b28;
    uRam011f686c = uRam011f6b2c;

    // If camera pointer exists and has valid projection matrix (offset +0x48)
    if ((DAT_012058e8 != 0) && (*(int *)(DAT_012058e8 + 0x48) != 0))
    {
        // Transform the second matrix using camera data: position/offset at +0x10, projection matrix at +0x48, store to g_workingMatrix1
        FUN_0060b020(*(undefined4 *)(DAT_012058e8 + 0x10), *(int *)(DAT_012058e8 + 0x48), &DAT_011f6830);
    }

    // Apply the final matrix (source at 0x011f6b70) – likely a concatenated view-projection
    FUN_00612210(&DAT_011f6b70);

    return;
}