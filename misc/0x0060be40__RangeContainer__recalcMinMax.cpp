// FUNC_NAME: RangeContainer::recalcMinMax
// Address: 0x0060be40
// This function recalculates the minimum and maximum values from an array of unsigned shorts.
// The class has: m_count (uint at +0x0c), m_min (ushort at +0x10), m_max (ushort at +0x12),
// and a pointer to the data array at +0x14.

void __thiscall RangeContainer::recalcMinMax(void)
{
    ushort minVal;
    ushort maxVal;
    uint index;
    ushort currentVal;

    index = 0;
    maxVal = 0;
    minVal = 0xffff;
    if (*(uint *)(this + 0x0c) != 0) {
        do {
            // Read current element from array at +0x14
            currentVal = *(ushort *)(*(int *)(this + 0x14) + index * 2);
            if (currentVal < minVal) {
                minVal = currentVal;
            }
            if (maxVal <= currentVal) {
                maxVal = currentVal;
            }
            index = index + 1;
        } while (index < *(uint *)(this + 0x0c));
    }
    // Store computed min and max
    *(ushort *)(this + 0x12) = maxVal;
    *(ushort *)(this + 0x10) = minVal;
    return;
}