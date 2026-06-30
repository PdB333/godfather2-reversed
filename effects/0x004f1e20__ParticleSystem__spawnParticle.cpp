// FUNC_NAME: ParticleSystem::spawnParticle
// Address: 0x004f1e20
// Creates a new particle effect from a template object (param_1).
// Sets up global rendering state and allocates/registers a particle instance.

void __thiscall ParticleSystem::spawnParticle(void* thisPtr) {
    // Stack-based scoped guard (likely for profiling or resource tracking)
    char local_38; // Possibly a flag for blend mode
    undefined4 local_3c; // Part of the guard structure
    float local_30, uStack_2c, uStack_28; // Temporary vectors
    undefined4 uStack_14[2]; // Padding
    float local_20; // Common color (white)
    float* puVar4; // Allocated particle data buffer

    // Initialize scope guard with a value derived from thisPtr+0x60
    // the guard likely controls some engine state
    FUN_005334b0(&local_3c, (-(uint)(*(int*)((char*)thisPtr + 0x60) != 0) & 0xffffffc0) + 0x40);

    // Reset some global frame counter?
    FUN_00534ff0(0);

    // Clamp global quality settings (fog density? or particle limit?)
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 0; // Disable some effect flag
    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 1; // Enable another effect flag

    // Start particle rendering context
    FUN_004ec7a0();

    // Set default particle color (white)
    local_3c = DAT_00e2b1a4; // white RGBA?

    // Set color for the particle batch
    FUN_004eccc0(1);

    // Store spawn position (4 floats) into globals
    _DAT_01219b40 = *(float*)((char*)thisPtr + 0x10);
    _DAT_01219b44 = *(float*)((char*)thisPtr + 0x14);
    _DAT_01219b48 = *(float*)((char*)thisPtr + 0x18);
    _DAT_01219b4c = *(float*)((char*)thisPtr + 0x1c);

    // Optional: If the global reference matches a certain object and that object is valid,
    // call a function to attach the particle to that object (possible parent)
    if ((DAT_012058e8 == &DAT_01219a70) && (*(int*)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30) != 0)) {
        FUN_0060add0(DAT_01219a80, *(int*)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30), (char*)thisPtr + 0x10);
    }

    // Apply current transformation state
    FUN_00535220();

    // Set blend mode to additive? (0, 1.0f)
    if (local_38 == '\0') {
        FUN_00535450(0, 0x3f800000); // 1.0f
        local_38 = '\x01';
    }

    // Allocate memory for a new particle instance (5 elements of 4 bytes each? or an array of 32 floats?)
    puVar4 = (float*)FUN_0060cd00(5, 4, 0, 1, 0);
    if (puVar4 != nullptr) {
        // Copy particle template data from thisPtr into the buffer
        // Offsets correspond to: position, velocity, acceleration, color, etc.
        float v1, v2, v3, v4;
        v1 = *(float*)((char*)thisPtr + 0x50);
        v2 = *(float*)((char*)thisPtr + 0x24);
        v3 = *(float*)((char*)thisPtr + 0x28);
        puVar4[0] = *(float*)((char*)thisPtr + 0x20); // velocity x
        puVar4[1] = v2;              // velocity y
        puVar4[2] = v3;              // velocity z
        puVar4[3] = v1;              // velocity w? or something

        // Clear unused fields
        uStack_14[0] = 0;
        uStack_14[1] = 0;
        puVar4[4] = 0;
        puVar4[5] = 0;
        puVar4[6] = 0;
        puVar4[7] = 0;

        // Copy color
        local_20 = DAT_00e2b1a4; // white

        v2 = *(float*)((char*)thisPtr + 0x30);
        v3 = *(float*)((char*)thisPtr + 0x34);
        puVar4[8] = *(float*)((char*)thisPtr + 0x2c); // acceleration x?
        puVar4[9] = v2;           // acceleration y?
        puVar4[10] = v3;          // acceleration z?
        puVar4[11] = v1;          // extra
        puVar4[12] = local_20;    // color
        puVar4[13] = 0;
        puVar4[14] = 0;
        puVar4[15] = 0;

        // Next block: rotation, scale, etc.
        float uStack_24 = *(float*)((char*)thisPtr + 0x54);
        v1 = *(float*)((char*)thisPtr + 0x3c);
        v2 = *(float*)((char*)thisPtr + 0x40);
        puVar4[16] = *(float*)((char*)thisPtr + 0x38); // rotation or scale
        puVar4[17] = v1;
        puVar4[18] = v2;
        puVar4[19] = uStack_24;

        puVar4[20] = 0;
        puVar4[21] = local_20;
        puVar4[22] = 0;
        puVar4[23] = 0;

        // Last block: lifetime, etc.
        local_30 = *(float*)((char*)thisPtr + 0x44);
        uStack_2c = *(float*)((char*)thisPtr + 0x48);
        uStack_28 = *(float*)((char*)thisPtr + 0x4c);
        puVar4[24] = local_30;
        puVar4[25] = uStack_2c;
        puVar4[26] = uStack_28;
        puVar4[27] = uStack_24;

        puVar4[28] = local_20;
        puVar4[29] = local_20;
        puVar4[30] = 0;
        puVar4[31] = 0;

        // Register the particle in the engine's render list
        FUN_0060cde0();
    }

    // Destroy scope guard
    FUN_00533720(&local_3c);
    return;
}