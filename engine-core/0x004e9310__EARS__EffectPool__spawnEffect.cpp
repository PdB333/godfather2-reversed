// FUNC_NAME: EARS::EffectPool::spawnEffect
int __fastcall EARS::EffectPool::spawnEffect(byte effectType, float x, float y, uint param4, uint param5, uint param6, uint param7) {
    // Global counter of active effects, max 256
    if (g_activeEffectCount > 255) {
        return 0;
    }

    // Lock or begin allocation (mutex?)
    beginCriticalSection(); // FUN_0044d750

    // Build the effect spawn data (84-byte structure)
    EffectSpawnData data;
    data.type = effectType;                   // +0x00
    data.flags = 0x100;                        // +0x02 (bit flag)
    data.x = x;                               // +0x04
    data.minCoord = (y <= x) ? y : x;         // +0x08 (store the smaller of the two floats)
    data.param4 = param4;                     // +0x0C
    data.param5 = param5;                     // +0x10
    data.param6 = param6;                     // +0x14
    data.param7 = param7;                     // +0x18

    // Attempt to allocate/register the effect
    int result = createEffect(&data);         // FUN_0044ee30
    if (result != 0) {
        g_activeEffectCount++;
    }

    return result;
}