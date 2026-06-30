// FUNC_NAME: Transform::getPosition
void __thiscall Transform::getPosition(void* thisPtr, float* outX, float* outY, float* outZ) {
    // Offsets: +0x20 = x, +0x24 = y, +0x28 = z
    float x = *(float*)((char*)thisPtr + 0x20);
    float y = *(float*)((char*)thisPtr + 0x24);
    float z = *(float*)((char*)thisPtr + 0x28);
    if (outX != nullptr) *outX = x;
    if (outY != nullptr) *outY = y;
    if (outZ != nullptr) *outZ = z;
}