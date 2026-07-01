// FUNC_NAME: Entity::setVector4
void __thiscall Entity::setVector4(float* src) {
    // Copy 4 floats (16 bytes) from src to member array at +0x130
    float* dest = reinterpret_cast<float*>(this + 0x130 / 4);
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}