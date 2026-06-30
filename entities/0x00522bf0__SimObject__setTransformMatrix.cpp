// FUNC_NAME: SimObject::setTransformMatrix
void SimObject::setTransformMatrix(float (*src)[4]) // src assumed to be 4x4 matrix (16 floats)
{
    // Call initialization routines (likely identity or something)
    FUN_00424470(); // unknown init
    FUN_00417560(); // unknown init

    // Copy 16 float values from src into internal matrix at offset +0x60
    // Layout: 4x4 matrix (16 floats) at this+0x60
    // src is pointer to array of 16 floats, accessed as flat indices
    // We'll cast to float* and copy

    float* dstMatrix = (float*)(reinterpret_cast<uint8_t*>(this) + 0x60);
    for (int i = 0; i < 16; i++) {
        dstMatrix[i] = (*src)[i];
    }

    // Clear extra fields (could be flags, counters, etc.)
    *(int*)(reinterpret_cast<uint8_t*>(this) + 8) = 0;       // +0x08: some int
    *(int*)(reinterpret_cast<uint8_t*>(this) + 0xC) = 0;     // +0x0C: some int
    *(short*)(reinterpret_cast<uint8_t*>(this) + 0x10) = 0;  // +0x10: short
    *(short*)(reinterpret_cast<uint8_t*>(this) + 0x12) = 0;  // +0x12: short
    *(int*)(reinterpret_cast<uint8_t*>(this) + 0x14) = 0;    // +0x14: some int
}