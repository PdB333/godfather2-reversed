// FUNC_NAME: animCacheUpdateVectors
// Function address: 0x0060aea0
// Role: Updates a per-slot vector cache (array of 4-float vectors) from source data.
// Writes only if changed, then notifies system via vtable call.

struct Vector4 {
    float x, y, z, w;
};

// Global cache arrays - each slot holds one Vector4 (16 bytes)
// 256 slots, offset = slot * 16 (0x10)
static Vector4 s_animCacheLow[256];  // DAT_011d97f0
static Vector4 s_animCacheHigh[256]; // DAT_011ea8f0

// Global singleton pointer (e.g., AnimationManager)
extern void* g_animManager; // DAT_01205750

// Vtable function indices (relative to *g_animManager)
// +0x178: notifyCacheChangedHigh (no params)
// +0x1b4: notifyCacheChangedLow( void* manager, uint slotIndex, Vector4* cacheEntry, uint vectorCount )

void __cdecl animCacheUpdateVectors(uint flags, Vector4* source, int vectorCount) {
    if (flags == 0) return;

    // vectorCount is originally number of 4-float vectors, convert to byte count? No, keep as vector count.
    // param_4 was multiplied by 4 in original? Actually original param_4 is vector count.
    // The decompiled param_4 = param_4 * 4; but that seems to convert from vector count to float count? 
    // For clarity, assume vectorCount is number of vectors (each 4 floats). The code uses param_4 as float count.
    // So we multiply here to get float count for loops.
    int floatCount = vectorCount * 4; // each vector is 4 floats

    int slotIndex = flags & 0xFF;
    bool isHigh = (flags & 0x80000000) != 0;
    Vector4* destBase = isHigh ? &s_animCacheHigh[slotIndex] : &s_animCacheLow[slotIndex];
    float* dest = (float*)destBase;
    float* src = (float*)source;

    bool changed = false;

    // Main loop: process 4 floats at a time (one Vector4) with unrolled comparisons
    int processed = 0;
    if (floatCount > 3) {
        int fullVectors = (floatCount - 4) / 4 + 1; // number of vector iterations
        processed = fullVectors * 4;
        for (int i = 0; i < fullVectors; i++) {
            float* vecDest = dest + i * 4;
            float* vecSrc  = src  + i * 4;
            if (vecDest[0] != vecSrc[0]) { vecDest[0] = vecSrc[0]; changed = true; }
            if (vecDest[1] != vecSrc[1]) { vecDest[1] = vecSrc[1]; changed = true; }
            if (vecDest[2] != vecSrc[2]) { vecDest[2] = vecSrc[2]; changed = true; }
            if (vecDest[3] != vecSrc[3]) { vecDest[3] = vecSrc[3]; changed = true; }
        }
    }

    // Remainder floats (0 to 3)
    for (int i = processed; i < floatCount; i++) {
        if (dest[i] != src[i]) {
            dest[i] = src[i];
            changed = true;
        }
    }

    if (changed) {
        if (isHigh) {
            // Call notifyHigh (vtable +0x178)
            void* vtable = *(void**)g_animManager; // first word is vtable pointer
            void (*notifyFunc)() = (void (*)())(*((unsigned int*)vtable + 0x178/4)); // offset 0x178
            notifyFunc();
        } else {
            // Call notifyLow (vtable +0x1b4) with parameters: manager, slotIndex, destBase, vectorCount
            void* vtable = *(void**)g_animManager;
            void (*notifyFunc)(void*, uint, Vector4*, int) = 
                (void (*)(void*, uint, Vector4*, int))(*((unsigned int*)vtable + 0x1b4/4));
            notifyFunc(g_animManager, slotIndex, destBase, vectorCount);
        }
    }
}