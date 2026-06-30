// FUNC_NAME: DebugManager::storeDebugSnapshot
void DebugManager::storeDebugSnapshot(void)
{
    // Copy 16 dwords (64 bytes) from the source buffer pointed to by ESI into global debug snapshot storage
    // This appears to be a snapshot of debug state data (e.g., player position, camera, etc.)
    _DAT_011f68a0 = *unaff_ESI;                    // +0x00: First dword of snapshot
    uRam011f68a4 = unaff_ESI[1];                   // +0x04
    uRam011f68a8 = unaff_ESI[2];                   // +0x08
    uRam011f68ac = unaff_ESI[3];                   // +0x0C
    _DAT_011f68b0 = unaff_ESI[4];                  // +0x10
    uRam011f68b4 = unaff_ESI[5];                   // +0x14
    uRam011f68b8 = unaff_ESI[6];                   // +0x18
    uRam011f68bc = unaff_ESI[7];                   // +0x1C
    _DAT_011f68c0 = unaff_ESI[8];                  // +0x20
    uRam011f68c4 = unaff_ESI[9];                   // +0x24
    uRam011f68c8 = unaff_ESI[10];                  // +0x28
    uRam011f68cc = unaff_ESI[0xb];                 // +0x2C
    _DAT_011f68d0 = unaff_ESI[0xc];                // +0x30
    uRam011f68d4 = unaff_ESI[0xd];                 // +0x34
    uRam011f68d8 = unaff_ESI[0xe];                 // +0x38
    uRam011f68dc = unaff_ESI[0xf];                 // +0x3C

    // If there's an active debug renderer, update its debug visualizations
    if (DAT_012058e8 != 0) {
        // Update debug line renderer (if available)
        if (*(int *)(DAT_012058e8 + 0x40) != 0) {
            FUN_0060b020(*(undefined4 *)(DAT_012058e8 + 0x10), *(int *)(DAT_012058e8 + 0x40));
        }
        // Update debug triangle renderer (if available)
        if (*(int *)(DAT_012058e8 + 0x44) != 0) {
            FUN_0060aea0(*(undefined4 *)(DAT_012058e8 + 0x10), *(int *)(DAT_012058e8 + 0x44));
        }
    }
    return;
}