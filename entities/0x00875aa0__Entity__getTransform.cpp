// FUNC_NAME: Entity::getTransform
// Address: 0x00875aa0
// Role: Copies the 7-float transform (quaternion + translation) from the object at offset 0xe30 into the output buffer.
void __thiscall Entity::getTransform(float* outTransform) const
{
    // Quaternion (4 floats) at +0xe30
    outTransform[0] = *(float*)(this + 0xe30);
    outTransform[1] = *(float*)(this + 0xe34);
    outTransform[2] = *(float*)(this + 0xe38);
    outTransform[3] = *(float*)(this + 0xe3c);
    // Translation (3 floats) at +0xe40
    outTransform[4] = *(float*)(this + 0xe40);
    outTransform[5] = *(float*)(this + 0xe44);
    outTransform[6] = *(float*)(this + 0xe48);
}