// FUNC_NAME: AnimBlender::updateRandomBlend
// Reconstructed C++ from Ghidra decompile of 0x006a9510
// This function updates animation blend parameters with random interpolation and noise.
// It appears to drive a blend tree or playback controller for animations.

int __fastcall AnimBlender::updateRandomBlend(int this)
{
    float fVar1;
    char cVar2;
    char cVar3;
    uint uVar4;

    // Copy target blend values (at +0xDC, +0xE4) to previous blend values (+0xC4, +0xCC, +0xD0, +0xD8)
    *(long long *)(this + 0xC4) = *(long long *)(this + 0xDC);
    *(long long *)(this + 0xD0) = *(long long *)(this + 0xDC);
    *(int *)(this + 0xCC) = *(int *)(this + 0xE4);
    *(int *)(this + 0xD8) = *(int *)(this + 0xE4);

    // Override first blend weight with a global default (DAT_01205214)
    fVar1 = DAT_01205214;  // likely default blend weight
    *(float *)(this + 0xC4) = DAT_01205214;
    *(float *)(this + 0xD0) = fVar1;

    // Check if random noise flag is set or if current blend (0xBC) is below threshold
    if ((*(char *)(this + 0xE8) != '\0') || (*(float *)(this + 0xBC) < DAT_00e44598)) {
        if (*(char *)(this + 0xE9) == '\0') {
            // Generate random blend target for x component
            uVar4 = DAT_010c2678 & DAT_012054b4;  // mask and counter for random table
            DAT_012054b4 = DAT_012054b4 + 1;
            *(float *)(this + 0xDC) =
                (*(float *)(this + 0xA8) - *(float *)(this + 0xA4)) *  // range
                *(float *)(&DAT_010c2680 + uVar4 * 4) +                // random float in [0,1]
                *(float *)(this + 0xC4) +                               // base
                *(float *)(this + 0xA4);                                // offset
        } else {
            // Simple additive: add default to current blend
            *(float *)(this + 0xDC) = *(float *)(this + 0xBC) + fVar1;
            *(unsigned char *)(this + 0xE9) = 0;
        }
    } else {
        // Reset blend and set target to current + default
        *(int *)(this + 0xCC) = 0;
        *(float *)(this + 0xDC) = *(float *)(this + 0xBC) + fVar1;
    }

    // Generate random target for Y component
    uVar4 = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4 = DAT_012054b4 + 1;
    *(float *)(this + 0xE0) =
        (*(float *)(this + 0xB0) - *(float *)(this + 0xAC)) *
        *(float *)(&DAT_010c2680 + uVar4 * 4) +
        *(float *)(this + 0xAC);

    // Generate random target for Z component (or another axis)
    uVar4 = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4 = DAT_012054b4 + 1;
    *(float *)(this + 0xE4) =
        (*(float *)(this + 0xB8) - *(float *)(this + 0xB4)) *
        *(float *)(&DAT_010c2680 + uVar4 * 4) +
        *(float *)(this + 0xB4);

    // Get two random booleans to decide if we trigger a new blend cycle
    cVar2 = FUN_006a91d0();  // returns random bool
    cVar3 = FUN_006a91d0();
    if ((cVar2 == '\0') && (cVar3 == '\0')) {
        cVar2 = '\0';
    } else {
        cVar2 = '\x01';
    }
    *(char *)(this + 0xE8) = cVar2;

    if (cVar2 != '\0') {
        // Trigger new blend cycle: seed random with a global timer, clear flag, then recurse?
        FUN_00408680(&DAT_012069c4);  // likely random seed or timer update
        *(unsigned char *)(this + 0xE9) = 0;
        FUN_006a9870();                // calls this function again (or related update)
        return 1;
    }
    return 0;
}