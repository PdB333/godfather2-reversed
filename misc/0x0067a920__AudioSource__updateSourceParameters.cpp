// FUNC_NAME: AudioSource::updateSourceParameters

void AudioSource::updateSourceParameters(void) {
    int iVar1;
    uint uVar2;
    uint uVar3;

    // Local pan values (initialized to extremes)
    int16 panLeft = 0x7fff;           // +0x114 default
    int16 panRight = -0x7fff;         // +0x118 default (0xffff8001)
    int16 panCenter = 0x7fff;         // +0x11c default
    int16 panRear = 0;                // +0x120 default

    // Initialize fields to defaults
    *(int32_t *)(this + 0x110) = 0;
    *(int32_t *)(this + 0x114) = 0x7fff;
    *(int32_t *)(this + 0x118) = 0xffff8001;
    *(int32_t *)(this + 0x11c) = 0x7fff;

    // Branch based on flag at +0x24 (mode selector)
    if (*(int32_t *)(this + 0x24) == 0) {
        // If already zero, check again (appears redundant but matches original)
        if (*(int32_t *)(this + 0x24) == 0) goto LAB_0067a9e6;
        iVar1 = FUN_0067b8f0(7, &panLeft, &panRight, &panRear); // type 7
        if (iVar1 != 0) goto LAB_0067a9e6;
    } else {
        iVar1 = FUN_0067b8f0(2, &panLeft, &panRight, &panRear); // type 2
        if (iVar1 != 0) goto LAB_0067a989;
    }

    // Assign computed pan values (with sign handling)
    *(int32_t *)(this + 0x114) = (int32_t)panLeft;
    *(int32_t *)(this + 0x118) = -(int32_t)panRight;
    *(int32_t *)(this + 0x11c) = (int32_t)panCenter;
    *(int32_t *)(this + 0x120) = (int32_t)panRear;

LAB_0067a989:
LAB_0067a9e6:
    // Copy field +0xb8 to +0x124 (some reference)
    *(int32_t *)(this + 0x124) = *(int32_t *)(this + 0xb8);

    // Zero out a buffer at +0x100->+0xc, of length *(this+0x108) shorts
    uVar3 = 0;
    if (0 < *(int16_t *)(this + 0x108)) {
        uVar2 = 0;
        do {
            uVar3 = uVar3 + 1;
            *(int16_t *)(*(int32_t *)(*(int32_t *)(this + 0x100) + 0xc) + uVar2 * 2) = 0;
            uVar2 = (uint16_t)uVar3;
        } while ((int32_t)uVar2 < (int32_t)*(int16_t *)(this + 0x108));
    }

    // Handle case where panLeft is still default (0x7fff)
    if (*(int32_t *)(this + 0x114) == 0x7fff) {
        panRear = 0;
        uVar3 = FUN_0067bb50(&panRear); // query some value
        *(uint8_t *)(this + 0x1ec) = (uint8_t)(uVar3 & 0xff);
        if ((int16_t)panRear != 0) {
            iVar1 = FUN_0067aba0();
            if (iVar1 != 0) {
                *(int32_t *)(this + 0x114) = 0;
                FUN_00678240();
            }
        }
    }

    // Handle case where panRight is still default (-0x7fff)
    if (*(int32_t *)(this + 0x118) == -0x7fff) {
        panRear = 0;
        uVar3 = FUN_0067bb50(&panRear);
        *(uint8_t *)(this + 0x1ec) = (uint8_t)(uVar3 & 0xff);
        if ((int16_t)panRear != 0) {
            iVar1 = FUN_0067aba0();
            if (iVar1 != 0) {
                *(int32_t *)(this + 0x118) = 0;
                FUN_00678240();
            }
        }
    }

    // Set control flag at +0x110 to 32
    *(int32_t *)(this + 0x110) = 0x20;

    // Pan left: compute from value at +0x10c if still default
    if (*(int32_t *)(this + 0x114) == 0x7fff) {
        int32_t val = *(int32_t *)(this + 0x10c);
        *(int32_t *)(this + 0x114) = (val * 3 + ((int32_t)(val >> 31) & 3)) >> 2;
    }

    // Pan right: compute negative from value at +0x10c if still default
    if (*(int32_t *)(this + 0x118) == -0x7fff) {
        int32_t val = *(int32_t *)(this + 0x10c);
        *(int32_t *)(this + 0x118) = -((val + ((int32_t)(val >> 31) & 3)) >> 2);
    }

    // Pan center: compute from left, right, and field +0x10c if still default
    if (*(int32_t *)(this + 0x11c) == 0x7fff) {
        int32_t left = *(int32_t *)(this + 0x114);
        int32_t right = *(int32_t *)(this + 0x118);
        int32_t val = *(int32_t *)(this + 0x10c);
        *(int32_t *)(this + 0x11c) = (val - left) + right;
    }

    // Clamp pan center to non-negative
    if (*(int32_t *)(this + 0x11c) < 0) {
        *(int32_t *)(this + 0x11c) = 0;
    }

    return;
}