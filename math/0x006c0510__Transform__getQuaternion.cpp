// FUNC_NAME: Transform::getQuaternion
// Address: 0x006c0510
// Role: Copies the quaternion component from the object (stored at offsets +0x10..+0x1c) to an output array.

void __thiscall Transform::getQuaternion(Transform *this, float *outQuat) {
    // Fields are 4 consecutive floats at offsets 0x10, 0x14, 0x18, 0x1c
    outQuat[0] = *(float *)((uint8_t *)this + 0x10); // quaternion x
    outQuat[1] = *(float *)((uint8_t *)this + 0x14); // quaternion y
    outQuat[2] = *(float *)((uint8_t *)this + 0x18); // quaternion z
    outQuat[3] = *(float *)((uint8_t *)this + 0x1c); // quaternion w
}