// FUNC_NAME: sumRandomizedScores
float __fastcall sumRandomizedScores(void* thisPtr) {
    uint count = *(uint*)((char*)thisPtr + 0x1a8); // +0x1a8: number of iterations
    float total = 0.0f;

    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            int index = getSomeIndex(); // returns a random/selected index
            total += *(float*)((char*)thisPtr + 0x1b0 + index * 4); // +0x1b0: array of float values indexed by index
        }
    }

    return (float)total; // float10 conversion
}