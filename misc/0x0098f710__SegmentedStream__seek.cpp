// FUNC_NAME: SegmentedStream::seek
bool __thiscall SegmentedStream::seek(uint position, void* param_3) {
    // +0x48 : uint m_totalSize
    // +0x40 : int m_numSegments
    // +0x3c : int** m_segments   // array of 8-byte entries: [4-byte pointer to segment info, 4-byte unused?]
    // +0x4c : uint m_currentPosition

    bool success = false;
    if (position < *(uint*)(this + 0x48)) { // within total size
        uint segmentIndex = 0;
        int* segmentArray = *(int**)(this + 0x3c); // base pointer to segment array
        if (*(int*)(this + 0x40) != 0) { // segments exist
            int* segmentEntryPtr = segmentArray + 1; // skip first 4 bytes? Actually offset by 4 bytes.
            // Actually: piVar3 = (int*)(*(int*)(param_1+0x3c) + 4); So start at base+4
            uint remainingOffset = position;
            while ( remainingOffset >= *(uint*)(*segmentEntryPtr + 8) ) {
                segmentIndex++;
                remainingOffset -= *(uint*)(*segmentEntryPtr + 8);
                segmentEntryPtr += 2; // advance 8 bytes (two ints)
                if (*(int*)(this + 0x40) <= segmentIndex) {
                    return false; // went past last segment
                }
            }
            FUN_0098f230(remainingOffset, param_3); // set internal pointer to offset within segment
            *(uint*)(this + 0x4c) = position; // store current position
            success = true;
        }
    }
    return success;
}