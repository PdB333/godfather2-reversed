// FUNC_NAME: ParticleTemplate::applyToParticleInstance
void __thiscall ParticleTemplate::applyToParticleInstance(
    float* sourceMatrix1,          // +0x00 param_1: first 4x4 matrix source
    ParticleInstance* dest,        // param_2: target particle data
    unsigned int index,            // param_3: lookup table index (0..0xFFF)
    unsigned int param4,           // param_4: extra data stored at dest+0x1F4
    unsigned int param5,           // param_5: extra data stored at dest+0x1F8
    unsigned int param6            // param_6: extra data stored at dest+0x1FC
) {
    // The 'this' pointer (ECX) points to the second source matrix (16 floats)
    float* sourceMatrix2 = (float*)this; // second 4x4 matrix source

    // Store the scalar parameters into the particle instance
    dest->index = index;                                        // dest+0x1F0
    dest->extraParam1 = param4;                                 // dest+0x1F4 (500 decimal)
    dest->extraParam2 = param5;                                 // dest+0x1F8
    dest->extraParam3 = param6;                                 // dest+0x1FC

    // Copy first 4x4 matrix (sourceMatrix1) to dest->matrixA (offset 0x210)
    dest->matrixA[0]  = sourceMatrix1[0];
    dest->matrixA[1]  = sourceMatrix1[1];
    dest->matrixA[2]  = sourceMatrix1[2];
    dest->matrixA[3]  = sourceMatrix1[3];
    dest->matrixA[4]  = sourceMatrix1[4];
    dest->matrixA[5]  = sourceMatrix1[5];
    dest->matrixA[6]  = sourceMatrix1[6];
    dest->matrixA[7]  = sourceMatrix1[7];
    dest->matrixA[8]  = sourceMatrix1[8];
    dest->matrixA[9]  = sourceMatrix1[9];
    dest->matrixA[10] = sourceMatrix1[10];
    dest->matrixA[11] = sourceMatrix1[11];
    dest->matrixA[12] = sourceMatrix1[12];
    dest->matrixA[13] = sourceMatrix1[13];
    dest->matrixA[14] = sourceMatrix1[14];
    dest->matrixA[15] = sourceMatrix1[15];

    // Copy second 4x4 matrix (this) to dest->matrixB (offset 0x250)
    dest->matrixB[0]  = sourceMatrix2[0];
    dest->matrixB[1]  = sourceMatrix2[1];
    dest->matrixB[2]  = sourceMatrix2[2];
    dest->matrixB[3]  = sourceMatrix2[3];
    dest->matrixB[4]  = sourceMatrix2[4];
    dest->matrixB[5]  = sourceMatrix2[5];
    dest->matrixB[6]  = sourceMatrix2[6];
    dest->matrixB[7]  = sourceMatrix2[7];
    dest->matrixB[8]  = sourceMatrix2[8];
    dest->matrixB[9]  = sourceMatrix2[9];
    dest->matrixB[10] = sourceMatrix2[10];
    dest->matrixB[11] = sourceMatrix2[11];
    dest->matrixB[12] = sourceMatrix2[12];
    dest->matrixB[13] = sourceMatrix2[13];
    dest->matrixB[14] = sourceMatrix2[14];
    dest->matrixB[15] = sourceMatrix2[15];

    // Look up data from global particle parameter table (0x38 bytes per entry)
    // Index must be less than 0x1000 (4096)
    if (index < 0x1000) {
        ParticleParamEntry* entry = &gParticleParamTable[index];
        dest->floatValue1 = (float)entry->field2;  // ushort at offset 2
        dest->floatValue2 = (float)entry->field4;  // ushort at offset 4
    } else {
        dest->floatValue1 = 0.0f;
        dest->floatValue2 = 0.0f;
    }

    // If the destination is the current active particle instance, trigger an update
    if (gCurrentParticleInstance == dest) {
        ParticleSystem::onActiveParticleUpdated(); // FUN_00492190
    }
}