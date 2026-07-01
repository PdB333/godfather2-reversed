// FUNC_NAME: Vector3::setByFlags
// Address: 0x007996e0
// Role: Computes a vector based on bit flags, combining two source vectors (from global getters) and optionally a third.
// The function uses DAT_00e44564 which is assumed to be 0.0f (so subtractions become negations).
// Flags:
//   0x01 = sum of source1 and source2
//   0x02 = copy source1
//   0x04 = source1 - source2
//   0x08 = negated source2
//   0x10 = -(source1 + source2) then normalize
//   0x20 = negated source1
//   0x40 = source2 - source1
//   0x80 = copy source2
//   0x100 = negated source3 (from a third pointer)

void __thiscall Vector3::setByFlags(float *this, uint flags)
{
    float fVar1, fVar2, fVar3;
    float *pSource1, *pSource2, *pSource3;
    float negX1, negY1, negZ1; // negated source1
    float negX2, negY2, negZ2; // negated source2
    float tempX, tempY, tempZ;

    // Get pointers to source vectors (likely from global or static data)
    pSource1 = (float *)FUN_00471610(); // +0x20, +0x24, +0x28
    pSource2 = (float *)FUN_00471610(); // +0x00, +0x04, +0x08
    pSource3 = (float *)FUN_00471610(); // +0x10, +0x14, +0x18

    // Read source vectors
    fVar1 = pSource1[0x20 / 4]; // x1
    fVar2 = pSource1[0x24 / 4]; // y1
    fVar3 = pSource1[0x28 / 4]; // z1

    // Compute negations (assuming DAT_00e44564 == 0.0f)
    negX1 = -fVar1;
    negY1 = -fVar2;
    negZ1 = -fVar3;
    negX2 = -pSource2[0];
    negY2 = -pSource2[1];
    negZ2 = -pSource2[2];

    if (flags < 0x11) {
        if (flags == 0x10) {
            // Case 0x10: -(source1 + source2) then normalize
            tempX = negX2 + negX1; // -(x1 + x2)
            tempY = negY2 + negY1; // -(y1 + y2)
            tempZ = negZ2 + negZ1; // -(z1 + z2)
            this[0] = tempX;
            this[1] = tempY;
            this[2] = tempZ;
            FUN_0056afa0(&tempX, &tempX); // normalize in place
            this[0] = tempX;
            this[1] = tempY;
            this[2] = tempZ;
            return;
        }
        switch (flags) {
        case 1:
            // Case 1: source1 + source2
            this[0] = pSource2[0] + fVar1;
            this[1] = pSource2[1] + fVar2;
            this[2] = pSource2[2] + fVar3;
            break;
        case 2:
            // Case 2: copy source1
            this[0] = fVar1;
            this[1] = fVar2;
            this[2] = fVar3;
            return;
        case 4:
            // Case 4: source1 - source2
            this[0] = fVar1 + negX2; // x1 - x2
            this[1] = fVar2 + negY2; // y1 - y2
            this[2] = fVar3 + negZ2; // z1 - z2
            break;
        case 8:
            // Case 8: negated source2
            this[0] = negX2;
            this[1] = negY2;
            this[2] = negZ2;
            return;
        default:
            goto zero;
        }
        FUN_0043a210(); // unknown side effect
        return;
    }

    switch (flags) {
    case 0x20:
        // Case 0x20: negated source1
        this[0] = negX1;
        this[1] = negY1;
        this[2] = negZ1;
        return;
    case 0x40:
        // Case 0x40: source2 - source1
        this[0] = pSource2[0] + negX1; // x2 - x1
        this[1] = pSource2[1] + negY1; // y2 - y1
        this[2] = pSource2[2] + negZ1; // z2 - z1
        FUN_0043a210();
        return;
    case 0x80:
        // Case 0x80: copy source2
        this[0] = pSource2[0];
        this[1] = pSource2[1];
        this[2] = pSource2[2];
        return;
    case 0x100:
        // Case 0x100: negated source3
        this[0] = -pSource3[0x10 / 4];
        this[1] = -pSource3[0x14 / 4];
        this[2] = -pSource3[0x18 / 4];
        return;
    }

zero:
    this[0] = 0.0f;
    this[1] = 0.0f;
    this[2] = 0.0f;
}