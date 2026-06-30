// FUNC_NAME: Entity::getRotationQuaternion
void __thiscall Entity::getRotationQuaternion(float *outQuat) const
{
    // Copy the 4-component quaternion from the object's transform data.
    // Offsets relative to this:
    // +0x60: quaternion x
    // +0x64: quaternion y
    // +0x68: quaternion z
    // +0x6c: quaternion w
    outQuat[0] = *(float *)(this + 0x60);
    outQuat[1] = *(float *)(this + 100); // +0x64
    outQuat[2] = *(float *)(this + 0x68);
    outQuat[3] = *(float *)(this + 0x6c);
}