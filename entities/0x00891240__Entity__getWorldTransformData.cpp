// FUNC_NAME: Entity::getWorldTransformData
void __thiscall Entity::getWorldTransformData(float *outData) {
    // +0x20: Quaternion rotation x
    outData[0] = *(float *)(this + 0x20);
    // +0x24: Quaternion rotation y
    outData[1] = *(float *)(this + 0x24);
    // +0x28: Quaternion rotation z
    outData[2] = *(float *)(this + 0x28);
    // +0x2C: Quaternion rotation w
    outData[3] = *(float *)(this + 0x2C);
    // +0x170: Unknown value (maybe position x or secondary vector component)
    outData[5] = *(float *)(this + 0x170);
    // +0x174: Unknown value (maybe position y or secondary vector component)
    outData[4] = *(float *)(this + 0x174);
    // Note: indices 4 and 5 are swapped relative to memory order; likely a struct field reordering
}