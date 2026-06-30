// FUNC_NAME: ParticleEmitter::initializeParticle
void __thiscall ParticleEmitter::initializeParticle(int param_1, float *outputFloat)
{
    // this points to the particle object (unaff_ESI)
    // in_EAX is an implicit pointer to a matrix of 16 floats (passed in EAX register?)
    // We treat it as an additional hidden parameter.
    float *matrixData = (float *)in_EAX;

    // Copy matrix data into particle's transform matrix at offsets 0x50-0x8C
    // +0x50 to +0x8C: 16 floats, likely a 4x4 matrix
    for (int i = 0; i < 16; i++) {
        *(float *)((int)this + 0x50 + i * 4) = matrixData[i];
    }

    // +0x10: store the parameter (likely an ID or parent pointer)
    *(int *)((int)this + 0x10) = param_1;

    // +0x14 and +0x18 are zeroed
    *(int *)((int)this + 0x14) = 0;
    *(int *)((int)this + 0x18) = 0;

    // Get parent object from +0x10 (now set to param_1)
    int parent = *(int *)((int)this + 0x10);

    // +0x1c: initial value from parent +0x70
    float baseValue = *(float *)(parent + 0x70);
    *(float *)((int)this + 0x1c) = baseValue;

    // If parent's scale factor (+0x74) is nonzero, add random offset scaled by it
    if (*(float *)(parent + 0x74) != 0.0f) {
        float random = randomFloat(); // FUN_004e41b0 returns a float [0,1)
        *(float *)((int)this + 0x1c) += random * *(float *)(parent + 0x74);
    }

    // Global constant from DAT_00e2b1a4 (likely a default value)
    float globalConst = DAT_00e2b1a4; // unknown global
    randomFloat(); // discard (fVar6 set to 0 but then used in next lines)

    // Check flag bit 0 of parent's attribute byte at +0x44
    if ((*(unsigned char *)(parent + 0x44) & 1) == 0) {
        // Bit 0 clear: no rotational spread
        *outputFloat = 0.0f;
        *(float *)((int)this + 0x38) = globalConst;
        *(float *)((int)this + 0x3c) = 0.0f;
    } else {
        // Bit 0 set: compute random angle spread
        float randomAngle = randomFloat() * DAT_00e44760; // DAT_00e44760 likely 2*PI or max angle
        *outputFloat = randomAngle;
        // +0x3c = sin(randomAngle)?
        *(float *)((int)this + 0x3c) = sinf(randomAngle); // FUN_00b99fcb likely sin
        // +0x38 = cos(randomAngle)?
        *(float *)((int)this + 0x38) = cosf(randomAngle); // FUN_00b99e20 likely cos
    }

    // Check flag bit 1 of parent's attribute byte (velocity spread)
    if ((*(unsigned char *)(parent + 0x44) & 2) != 0) {
        // Bit 1 set: compute velocity components using random and parent scales
        float randomScale = randomFloat();
        // +0x20 = randomScale * parent->scaleX * parent->scaleVelX?
        int iVar1 = *(int *)((int)this + 0x10); // parent again
        float velX = (float)(int)(randomScale * *(float *)(iVar1 + 0x4c)) * *(float *)(iVar1 + 0xb0);
        *(float *)((int)this + 0x20) = velX;

        // recompute randomScale? Actually fVar6 used again, but it's reset by randomFloat call
        float randomScale2 = randomFloat();
        float velY = (float)(int)(randomScale2 * *(float *)(iVar1 + 0x50)) * *(float *)(iVar1 + 0xb4);
        *(float *)((int)this + 0x24) = velY;
    } else {
        // No velocity spread, zero out velocity fields
        *(float *)((int)this + 0x20) = 0.0f;
        *(float *)((int)this + 0x24) = 0.0f;
    }

    return;
}