// FUNC_NAME: Entity::getOrientation
void __thiscall Entity::getOrientation(int thisPtr, float* outQuaternion)
{
    // Copy 4 floats from offsets 0x90, 0x94, 0x98, 0x9c (quaternion x,y,z,w)
    outQuaternion[0] = *(float*)(thisPtr + 0x90);
    outQuaternion[1] = *(float*)(thisPtr + 0x94);
    outQuaternion[2] = *(float*)(thisPtr + 0x98);
    outQuaternion[3] = *(float*)(thisPtr + 0x9c);
}