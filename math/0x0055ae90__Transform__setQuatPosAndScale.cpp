// FUNC_NAME: Transform::setQuatPosAndScale
void __thiscall Transform::setQuatPosAndScale(float* srcQuat, float* srcPos, float scale)
{
    // Copy 4-component quaternion from srcQuat to this at +0x10
    this->quaternion.x = srcQuat[0];  // +0x10
    this->quaternion.y = srcQuat[1];  // +0x14
    this->quaternion.z = srcQuat[2];  // +0x18
    this->quaternion.w = srcQuat[3];  // +0x1c

    // Copy 4-component position (w may be padding or 1.0) from srcPos to this at +0x20
    this->position.x = srcPos[0];     // +0x20
    this->position.y = srcPos[1];     // +0x24
    this->position.z = srcPos[2];     // +0x28
    this->position.w = srcPos[3];     // +0x2c

    // Store uniform scale at +0x30
    this->uniformScale = scale;       // +0x30
}