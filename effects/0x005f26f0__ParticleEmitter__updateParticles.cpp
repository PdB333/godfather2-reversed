// FUNC_NAME: ParticleEmitter::updateParticles
// Function address: 0x005f26f0
// Role: Updates particle properties (size, color, etc.) for all active particles in an emitter.
// Parameters: this (param_1), emitterData (param_2), deltaTime (param_3)
uint __thiscall ParticleEmitter::updateParticles(void* this, void* emitterData, float* deltaTime)
{
    byte particleCount;
    int iVar2;
    uint returnValue;
    int iVar4;
    undefined4 uVar5;
    int* particlePtrArray;
    float sizeFactor;

    returnValue = (uint)this & 0xffffff00; // Preserve high bits of 'this' for return

    if ((this != 0) && (emitterData != 0)) {
        // Pre-update call (possibly debug or state reset)
        FUN_005f2680();

        particleCount = *(byte*)((int)emitterData + 0x6f); // Particle count (max 255)
        sizeFactor = 0.0f;
        // Check if a flag at +8 (in a sub-structure at emitterData+8) has bit 1 set
        if ((*(byte*)(*(int*)((int)emitterData + 8) + 8) & 2) != 0) {
            // Retrieve a base size from the same sub-structure at offset 0x24
            sizeFactor = *(float*)(*(int*)((int)emitterData + 8) + 0x24);
        }

        // Iterate over array of particle pointers starting at emitterData+0xC
        particlePtrArray = (int*)((int)emitterData + 0xC);
        for (; particlePtrArray < (int*)((int)emitterData + 0xC + (uint)particleCount * 4); particlePtrArray++) {
            if ((particlePtrArray != 0) && (iVar2 = *particlePtrArray, iVar2 != 0)) {
                // Read byte at particle offset 0x1C (e.g., alpha/age), scale by deltaTime
                iVar4 = (int)(short)((float)*(byte*)(iVar2 + 0x1C) * *deltaTime);
                // Update particle rendering properties (color, size, etc.)
                // Parameters: scaled value, scaled value, sizeFactor, deltaTime, emitterData->+0x54
                FUN_005dbc10(iVar4, iVar4, (double)sizeFactor, (double)*deltaTime,
                             (double)*(float*)((int)emitterData + 0x54));
                // Set particle color or tint from this->+4
                *(undefined4*)(iVar2 + 0xC) = *(undefined4*)((int)this + 4);
                // Post-update calls (possibly commit changes)
                uVar5 = FUN_005f37b0();
                FUN_005f1400(uVar5);
            }
        }
        // Return value: combine high bits of 'this' with success flag (1)
        returnValue = (uint)particlePtrArray | 1; // Equivalent to CONCAT31(high,1)
    }
    return returnValue;
}