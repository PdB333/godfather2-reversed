// FUN_005d9d40: DataList::advanceIterator
void __thiscall DataList::advanceIterator(int *iteratorOut, int source, int target)
{
    uint startIndex = *(uint *)(this + 8);   // +0x8: m_startIndex
    uint endIndex   = *(uint *)(this + 0xC); // +0xC: m_endIndex
    int elementSize = 0x28;                  // 40 bytes per element
    int index;

    // If the list is not empty
    if (startIndex != 0) {
        int range = endIndex - startIndex;
        int signBit = range >> 31;          // arithmetic shift for sign extension
        // Check if target index is within valid range (range / elementSize > 0)
        if (range / elementSize + signBit != signBit) {
            // Validate source pointer: must be this (or null)
            if (source == 0 || source != (int)this) {
                FUN_00b97aea(); // assert/error
            }
            // Compute index from target offset relative to startIndex
            index = (int)(target - startIndex) / elementSize;
            goto LAB_005d9da3;
        }
    }
    index = 0;

LAB_005d9da3:
    FUN_005da1d0(1, source, target); // validation or processing call
    startIndex = *(uint *)(this + 8);
    if (*(uint *)(this + 0xC) < startIndex) {
        FUN_00b97aea(); // assert
    }
    uint newOffset = startIndex + index * elementSize;
    if (*(uint *)(this + 0xC) < newOffset || newOffset < *(uint *)(this + 8)) {
        FUN_00b97aea(); // assert bounds
    }
    // Set output iterator: container pointer and current offset
    iteratorOut[0] = (int)this;          // +0x00: container
    iteratorOut[1] = (int)newOffset;     // +0x04: current position
    return;
}