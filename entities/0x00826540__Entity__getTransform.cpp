// FUNC_NAME: Entity::getTransform
// Address: 0x00826540
// Returns a 5-element transform (position + rotation quaternion? or matrix row) based on a flag at offset +0x88.
// When flag is zero, uses primary transform at offsets 0x5c-0x6c; otherwise uses secondary at 0x8c-0x9c.

void __thiscall Entity::getTransform(void* thisPtr, float* outTransform)
{
    bool useSecondary = *(char*)((int)thisPtr + 0x88) != 0;

    if (!useSecondary) {
        outTransform[0] = *(float*)((int)thisPtr + 0x5c);
        outTransform[1] = *(float*)((int)thisPtr + 0x60);
        outTransform[2] = *(float*)((int)thisPtr + 0x64);
        outTransform[3] = *(float*)((int)thisPtr + 0x68);
        outTransform[4] = *(float*)((int)thisPtr + 0x6c);
    } else {
        outTransform[0] = *(float*)((int)thisPtr + 0x8c);
        outTransform[1] = *(float*)((int)thisPtr + 0x90);
        outTransform[2] = *(float*)((int)thisPtr + 0x94);
        outTransform[3] = *(float*)((int)thisPtr + 0x98);
        outTransform[4] = *(float*)((int)thisPtr + 0x9c);
    }
}