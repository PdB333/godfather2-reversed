// FUNC_NAME: Ray::set
void __thiscall Ray::set(float* originAndDir, float* dirZ) {
    // +0x08: origin.x
    *(float*)(this + 0x08) = originAndDir[0];
    // +0x0C: origin.y
    *(float*)(this + 0x0C) = originAndDir[1];
    // +0x10: origin.z
    *(float*)(this + 0x10) = originAndDir[2];
    // +0x14: direction.x
    *(float*)(this + 0x14) = originAndDir[3];
    // +0x18: direction.y
    *(float*)(this + 0x18) = originAndDir[4];
    // +0x1C: direction.z
    *(float*)(this + 0x1C) = *dirZ;
}