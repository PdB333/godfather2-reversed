// FUNC_NAME: ForceAccumulator::addForceFromSource
void ForceAccumulator::addForceFromSource(int thisPtr, int sourcePtr)
{
    struct Vec2 { float x; float y; }; // array of 2D vectors at offset 0x2ec, stride 8

    uint flags = *(uint *)(thisPtr + 0x18);
    if ((flags >> 1) & 1) // check bit 1 (enable flag)
    {
        int conditionId = *(int *)(sourcePtr + 0x18);
        int compareId = 0;
        if (conditionId != 0)
            compareId = conditionId - 0x48; // subtract offset to get raw ID

        // Condition: match this->localId (at +0x08) or pass the relationship check
        if (compareId == *(int *)(thisPtr + 8) || FUN_00785ee0(compareId) != 0)
        {
            int arrayIndex = *(int *)(sourcePtr + 4); // index into force array
            Vec2 *forceArray = (Vec2 *)(thisPtr + 0x2ec);
            // Add the force component to accumulated totals
            *(float *)(thisPtr + 0xc) += forceArray[arrayIndex].x;
            *(float *)(thisPtr + 0x2d8) += forceArray[arrayIndex].y;
        }
    }
}