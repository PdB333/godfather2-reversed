//FUNC_NAME: AnimationManager::updateTransformData
void __thiscall AnimationManager::updateTransformData(uint flags, float* sourceData)
{
    uint index = flags & 0xFF;
    bool changed = false;
    float* destBase;

    // Select destination buffer based on high bit (local vs remote)
    if ((flags & 0x80000000) == 0) {
        destBase = &g_transformDataLocal[index * 4]; // +0x00 per entry, 4 floats
    } else {
        destBase = &g_transformDataRemote[index * 4]; // +0x00 per entry, 4 floats
    }

    int count = this->transformCount; // Number of floats to copy (e.g., bone count * 4)
    int i = 0;

    // Copy in chunks of 4 floats (quaternion or vector+scalar)
    if (count > 3) {
        float* src = sourceData + 3; // Start at offset 3 floats (for aligned access)
        float* dst = destBase + 1;   // Start at offset 1 float
        int chunks = (count - 4) / 4 + 1;
        i = chunks * 4;

        do {
            // Compare and copy each of the 4 floats
            if (dst[-1] != src[-3]) {
                dst[-1] = src[-3];
                changed = true;
            }
            float val = *(float*)((int)src + ((int)dst - (int)destBase)); // Equivalent to src[0] relative to dst
            if (dst[0] != val) {
                dst[0] = val;
                changed = true;
            }
            if (dst[1] != src[-1]) {
                dst[1] = src[-1];
                changed = true;
            }
            if (dst[2] != src[0]) {
                dst[2] = src[0];
                changed = true;
            }
            dst += 4;
            src += 4;
            chunks--;
        } while (chunks != 0);
    }

    // Copy remaining floats (less than 4)
    if (i < count) {
        float* dst = destBase + i;
        int remaining = count - i;
        do {
            float val = *(float*)((int)dst + ((int)sourceData - (int)destBase)); // Equivalent to sourceData[offset]
            if (*dst != val) {
                *dst = val;
                changed = true;
            }
            dst++;
            remaining--;
        } while (remaining != 0);
    }

    // Notify system if any data changed
    if (changed) {
        if ((flags & 0x80000000) != 0) {
            // Remote: call via vtable offset 0x178 (e.g., markDirtyRemote)
            (**(code**)(*g_animationManager + 0x178))();
        } else {
            // Local: call via vtable offset 0x1b4 with parameters
            int numQuads = (count + 3 + ((count + 3) >> 31 & 3)) >> 2; // ceil(count/4)
            (**(code**)(*g_animationManager + 0x1b4))(g_animationManager, index, destBase, numQuads);
        }
    }
}