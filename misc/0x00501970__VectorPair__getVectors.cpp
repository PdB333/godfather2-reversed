// FUNC_NAME: VectorPair::getVectors
void __thiscall VectorPair::getVectors(float* outVec1, float* outVec2) const
{
    // Copy first vector (4 floats) from offset 0x10
    outVec1[0] = *(float*)((uint8_t*)this + 0x10);
    outVec1[1] = *(float*)((uint8_t*)this + 0x14);
    outVec1[2] = *(float*)((uint8_t*)this + 0x18);
    outVec1[3] = *(float*)((uint8_t*)this + 0x1c);

    // Copy second vector (4 floats) from offset 0x20
    outVec2[0] = *(float*)((uint8_t*)this + 0x20);
    outVec2[1] = *(float*)((uint8_t*)this + 0x24);
    outVec2[2] = *(float*)((uint8_t*)this + 0x28);
    outVec2[3] = *(float*)((uint8_t*)this + 0x2c);
}