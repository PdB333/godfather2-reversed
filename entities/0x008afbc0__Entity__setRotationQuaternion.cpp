// FUNC_NAME: Entity::setRotationQuaternion
// Function address: 0x008afbc0
// Copies 16 bytes (4 floats) from source to this+0x44, likely the rotation quaternion (x,y,z,w) stored at offsets +0x44, +0x48, +0x4c, +0x50
void __thiscall Entity::setRotationQuaternion(Entity* this, const float* quat)
{
    *(float*)((uintptr_t)this + 0x44) = quat[0];
    *(float*)((uintptr_t)this + 0x48) = quat[1];
    *(float*)((uintptr_t)this + 0x4c) = quat[2];
    *(float*)((uintptr_t)this + 0x50) = quat[3];
}