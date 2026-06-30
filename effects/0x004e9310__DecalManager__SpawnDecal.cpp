// FUNC_NAME: DecalManager::SpawnDecal
int DecalManager::SpawnDecal(uint8_t decalType, float x, float y, uint32_t param4, uint32_t param5, uint32_t param6, uint32_t param7, uint16_t flags)
{
    // Global counter of active decals (max 256)
    if (g_decalCount > 255) {
        return 0;
    }

    // Prepare decal creation info buffer
    DecalCreateInfo info; // 120 bytes on stack, offset 0x00-0x77

    // Reset or initialize part of the struct? Not clear.
    // FUN_0044d750 might be a memset or prepare function.
    FUN_0044d750(&info);

    // Set flags field at offset 0x56 (2 bytes) - OR with 0x100
    info.flags = flags | 0x100;

    // Copy parameters into structure fields at specific offsets
    // Offset 0x54: decal type (1 byte)
    info.decalType = decalType;

    // Offset 0x6C: x coordinate (float)
    info.positionX = x;

    // Offset 0x74: y coordinate, but clamped to min(x, param3)
    if (y <= x) {
        info.positionY = y;
    } else {
        info.positionY = x; // Actually use param3? Wait: local_3c = min(param2, param3); but here param2 is x? Confusing.
        // Re-analyzing: param2 is first float, param3 second float. They are x and y? The min logic:
        // if (param3 <= param2) then local_3c = param3; else local_3c = param2; So it stores the smaller.
        // So info.minFloat = min(param2, param3);
    }

    // Actually we need to match the variables correctly:
    // The decompiler says:
    // if (param_3 <= param_2) { local_3c = param_3; } else { local_3c = param_2; }
    // So local_3c is the minimum of param_2 and param_3.
    // But param_2 = x, param_3 = y.
    // Also local_44 = param_2 (x).
    // So structure has fields at offsets 0x44 (x) and 0x3C (min).
    // We'll define structure accordingly.

    info.unkFloat1 = x;          // +0x44
    if (y <= x) {
        info.minFloat = y;       // +0x3C
    } else {
        info.minFloat = x;
    }
    info.unkFloat2 = x;          // +0x3C? Wait conflict: same offset. Actually from code: local_3c gets min, and local_44 gets param_2. So they are different offsets.
    // Let's map offsets correctly:
    // local_44 at EBP-0x44 -> offset 0x6C from info base (since info base at EBP-0xB0)
    // local_3c at EBP-0x3C -> offset 0x74 from info base.
    // So:
    info.param2Copy = x;        // +0x6C
    info.minParam2Param3 = (y <= x) ? y : x; // +0x74

    // Continue with other parameters:
    info.param4 = param4;       // +0x40? Actually local_40 at -0x40 -> offset 0x70
    info.param5 = param5;       // +0x38? local_38 at -0x38 -> offset 0x78
    info.param6 = param6;       // +0x50? local_50 at -0x50 -> offset 0x60
    info.param7 = param7;       // +0x48? local_48 at -0x48 -> offset 0x68

    // Now call the actual creation function with pointer to struct
    int result = FUN_0044ee30(&info);

    // If successful, increment global counter
    if (result != 0) {
        g_decalCount++;
    }

    return result;
}