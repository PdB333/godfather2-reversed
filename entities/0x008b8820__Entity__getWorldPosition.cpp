// FUNC_NAME: Entity::getWorldPosition
float * __thiscall Entity::getWorldPosition(int this, float *outPos)
{
    outPos[0] = 0.0f;
    outPos[1] = 0.0f;
    outPos[2] = 0.0f;

    // Get reference position (likely camera or world origin offset)
    int refPtr = getReferencePosition(); // 0x00471610

    // Add object's local offset (position) to the reference
    // +0x1FC, +0x200, +0x204 are object's local position (x, y, z)
    // +0x30, +0x34, +0x38 are reference position components (x, y, z)
    outPos[0] = *(float *)(this + 0x1FC) + *(float *)(refPtr + 0x30);
    outPos[1] = *(float *)(this + 0x200) + *(float *)(refPtr + 0x34);
    outPos[2] = *(float *)(this + 0x204) + *(float *)(refPtr + 0x38);

    return outPos;
}