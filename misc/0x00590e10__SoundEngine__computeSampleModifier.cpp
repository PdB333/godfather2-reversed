// FUNC_NAME: SoundEngine::computeSampleModifier
float SoundEngine::computeSampleModifier(SoundEngine* thisPtr, SoundData* data, SampleArrayInfo* info) {
    // data struct: +0x00 unknown, +0x01 byte (appears to be a presence flag or version)
    //              +0x04 float pointer (some base value), +0x0C some int (holds address to another struct with short at +0x02)
    // info struct: [0] = pointer to float array (curve table), [1] = size of that array (in elements)

    if (*(char*)((int)data + 1) < 0x01) {
        return 1.0f;
    }

    float* baseValuePtr = *(float**)((int)data + 4);
    int additionalData = *(int*)((int)data + 0x0C);

    FUN_00591160(); // Likely a lock/refcount increment or resource fetch

    float scale = DAT_00e2b1a4; // likely 1.0f (some global default)
    if (*(float*)((int)thisPtr + 0x104) != 0.0f && *baseValuePtr != 0.0f) {
        scale = *(float*)((int)thisPtr + 0x104) / *baseValuePtr;
    }

    unsigned int index = (unsigned int)*(short*)(additionalData + 2); // short at offset +2 of additionalData
    // Check if index is out of bounds relative to array size stored in info[1]
    if ((unsigned int)info[1] <= index) {
        int local4 = 0;
        FUN_00591c00(&local4); // Likely a clamp/resample/recalculate function
    }

    float result = *(float*)(info[0] + index * 4) * scale;
    if (result == 0.0f) {
        result = DAT_00e2b1a4;
    }
    return result;
}