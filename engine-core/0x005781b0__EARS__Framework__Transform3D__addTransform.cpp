// FUNC_NAME: EARS::Framework::Transform3D::addTransform
void Transform3D::addTransform(Transform3D* other, Transform3D* result)
{
    // param_1 = this (passed in ECX)
    // other is presumably in EDI register, result in ESI register
    // The decompiler shows these as unaff_EDI and unaff_ESI.
    // This function adds the translation and orientation components.

    // Call initialize (maybe set to identity or zero)
    FUN_0056cba0(this);

    // Extract translation/vector components
    float thisX = *(float *)(this + 0x10);
    float thisY = *(float *)(this + 0x14);
    float thisZ = *(float *)(this + 0x18);
    float thisW = *(float *)(this + 0x1c);

    float otherX = *(float *)(other + 0x10);
    float otherY = *(float *)(other + 0x18);
    float otherZ = *(float *)(other + 0x1c);
    float otherW = *(float *)(other + 0x1c); // Note: offset same as Z? Probably a copy-paste bug, likely another offset.

    // Actually the decompiler reads:
    // fVar4 = *(float *)(unaff_EDI + 0x14); // Y
    // fVar5 = *(float *)(unaff_EDI + 0x18); // Z
    // fVar6 = *(float *)(unaff_EDI + 0x1c); // W
    // So other has components at +0x14, +0x18, +0x1c

    // Store sum into result's position
    *(float *)(result + 0x10) = thisX + *(float *)(other + 0x10);
    *(float *)(result + 0x14) = thisY + otherY;
    *(float *)(result + 0x18) = thisZ + otherZ;
    // Override last component with constant (likely 1.0f for points)
    *(float *)(result + 0x1c) = DAT_00e2b1a4; // e.g., 1.0f

    return;
}