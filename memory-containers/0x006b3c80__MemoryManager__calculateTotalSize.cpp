// FUNC_NAME: MemoryManager::calculateTotalSize
int __thiscall MemoryManager::calculateTotalSize(int param2)
{
    int segmentSize1 = getSegmentSize(param2); // FUN_006b2360: returns size of block starting at param2
    int segmentSize2 = getSegmentSize(segmentSize1 + param2, this + 0x84); // FUN_006b2470: first call with offset
    int cumulativeSize = segmentSize1 + param2 + segmentSize2;
    int segmentSize3 = getSegmentSize(cumulativeSize, this + 0x9c); // FUN_006b2470: second call
    return segmentSize3 + (cumulativeSize - param2); // total size (excluding initial param2 offset)
}