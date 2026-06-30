// FUNC_NAME: SimObject::resetFromData

void SimObject::resetFromData(void) {
    float fVar1, fVar2, fVar3, fVar8;
    float sqrtVal, invLength;
    int iVar4, iVar5;
    int *piVar6;

    // Lock or begin update
    FUN_009f0190();
    if (*(void**)(this + 0x30) != 0) {
        // Unlock specific to owner
        FUN_009f01a0();
    }

    // Copy orientation/quaternion (4 floats at +0x10)
    *(float*)(this + 0x10) = *(float*)(source + 0x10);
    *(float*)(this + 0x14) = *(float*)(source + 0x14);
    *(float*)(this + 0x18) = *(float*)(source + 0x18);
    *(float*)(this + 0x1c) = *(float*)(source + 0x1c);

    // Copy additional vectors (maybe velocity/position extras)
    *(float*)(this + 0x34) = *(float*)(source + 0x20);
    *(float*)(this + 0x38) = *(float*)(source + 0x24);

    // Copy more physics data
    *(float*)(this + 0x50) = *(float*)(source + 0x40);
    *(float*)(this + 0x54) = *(float*)(source + 0x44);
    *(float*)(this + 0x58) = *(float*)(source + 0x4c);
    *(void**)(this + 0x30) = *(void**)(source + 0x48); // owner pointer
    *(float*)(this + 0x5c) = *(float*)(source + 0x50);
    *(float*)(this + 0x60) = *(float*)(source + 0x54);

    *(char*)(this + 0x94) = *(char*)(source + 0x58); // some byte flag

    // Copy direction/normal vector (4 floats at +0x40)
    *(float*)(this + 0x40) = *(float*)(source + 0x30);
    *(float*)(this + 0x44) = *(float*)(source + 0x34);
    *(float*)(this + 0x48) = *(float*)(source + 0x38);
    *(float*)(this + 0x4c) = *(float*)(source + 0x3c);

    // Normalize the direction vector
    fVar1 = *(float*)(this + 0x44);
    fVar2 = *(float*)(this + 0x40);
    fVar3 = *(float*)(this + 0x48);
    fVar8 = fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3;
    if (fVar8 == 0.0f) {
        invLength = 0.0f;
    } else {
        sqrtVal = (float)FUN_00414a80(fVar8);   // sqrt
        invLength = 1.0f / sqrtVal;
    }
    *(float*)(this + 0x48) = fVar3 * invLength;
    *(float*)(this + 0x40) = fVar2 * invLength;
    *(float*)(this + 0x44) = fVar1 * invLength;
    *(float*)(this + 0x4c) = *(float*)(this + 0x4c) * invLength;

    // Detach from current attachment if exists
    if (*(int*)(*(int*)(this + 0x30) + 8) != 0) {
        FUN_009f1820(source, 0); // detach source from parent
    }

    // Zero out linear/angular velocity (at +0x20..+0x2c)
    *(int*)(this + 0x2c) = 0;
    *(int*)(this + 0x28) = 0;
    *(int*)(this + 0x24) = 0;
    *(int*)(this + 0x20) = 0;

    // Clear a list of objects at +0x8 (count at +0x80)
    if (0 < *(int*)(this + 0x80)) {
        iVar5 = 0;
        do {
            FUN_009f2410(this + 8);   // remove from list
            iVar5 = iVar5 + 1;
        } while (iVar5 < *(int*)(this + 0x80));
    }
    *(int*)(this + 0x80) = 0;   // reset count

    // Clear another list at +0xc (count at +0x8c)
    if (0 < *(int*)(this + 0x8c)) {
        iVar5 = 0;
        do {
            FUN_00a0dec0(this + 0xc);   // remove from list
            iVar5 = iVar5 + 1;
        } while (iVar5 < *(int*)(this + 0x8c));
    }
    *(int*)(this + 0x8c) = 0;   // reset count

    *(int*)(this + 0x68) = 0;   // some flag/timer

    // Check if message 0x1300 is already registered in owner's table
    iVar5 = *(int*)(*(int*)(this + 0x30) + 0x78); // number of entries
    iVar4 = 0;
    if (0 < iVar5) {
        piVar6 = *(int**)(*(int*)(this + 0x30) + 0x74); // table pointer
        do {
            if (*piVar6 == 0x1300) {
                return; // already queued/fired, skip
            }
            iVar4 = iVar4 + 1;
            piVar6 = piVar6 + 4;
        } while (iVar4 < iVar5);
    }

    // Post a reset/init message to owner
    FUN_009f01f0(0x1300, this, 0); // (messageId, this, arg=0)
}