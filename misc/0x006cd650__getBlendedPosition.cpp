// FUNC_NAME: getBlendedPosition
void __thiscall getBlendedPosition(void* this, float* outPos)
{
    int obj1Base;
    int obj2Base;
    float pos1[3];
    float pos2[3];

    // +0xC0: pointer to first sub-object (like a bone or attachment)
    if (*(int*)((char*)this + 0xC0) == 0) {
        obj1Base = 0;
    } else {
        // The pointer points into a struct at offset +0x48; subtract to get base
        obj1Base = *(int*)((char*)this + 0xC0) - 0x48;
    }
    // Get world position from the first object
    getPosition(obj1Base, pos1);

    // +0xC8: pointer to second sub-object
    if (*(int*)((char*)this + 0xC8) == 0) {
        obj2Base = 0;
    } else {
        obj2Base = *(int*)((char*)this + 0xC8) - 0x48;
    }
    getPosition(obj2Base, pos2);

    // Global blend factor (likely from config or time scale)
    float factor = *(float*)0x00d5c458; // g_blendFactor

    // Blend the two positions using the factor
    outPos[0] = (pos2[0] + pos1[0]) * factor;
    outPos[1] = (pos2[1] + pos1[1]) * factor;
    outPos[2] = (pos2[2] + pos1[2]) * factor;
}