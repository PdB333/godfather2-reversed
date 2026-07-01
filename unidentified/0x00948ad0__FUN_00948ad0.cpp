// FUNC_NAME: UnknownClass::setQuaternion
void __thiscall UnknownClass::setQuaternion(float *quaternion) {
    if (quaternion != nullptr) {
        float w = quaternion[0];
        float x = quaternion[1];
        float y = quaternion[2];
        float z = quaternion[3];
        *(float *)(this + 0x140) = w;   // +0x140: quaternion.w
        *(float *)(this + 0x144) = x;   // +0x144: quaternion.x
        *(float *)(this + 0x148) = y;   // +0x148: quaternion.y
        *(float *)(this + 0x14c) = z;   // +0x14c: quaternion.z
    } else {
        *(float *)(this + 0x14c) = 0.0f;
        *(float *)(this + 0x148) = 0.0f;
        *(float *)(this + 0x144) = 0.0f;
        *(float *)(this + 0x140) = 0.0f;
    }
}