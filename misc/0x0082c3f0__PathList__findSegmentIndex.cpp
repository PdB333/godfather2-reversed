// FUNC_NAME: PathList::findSegmentIndex
// Function address: 0x0082c3f0
// Role: Searches a circular list of path segments to find the index of the segment that contains a given point.
// The list is stored as an array of pointers to segment structures, each with a data field at offset +0x4.
// The comparison function (0x00821840) checks if the point lies between two consecutive segment endpoints.

// Structure offsets:
// +0x00: vtable? (not used here)
// +0x04: currentIndex (uint) - last found index or starting point
// +0x08: segmentArray (int*) - pointer to array of pointers to segment data
// +0x0C: count (uint) - number of segments

// External comparison function: returns non-zero if point is between segmentA and segmentB
extern bool __cdecl isPointBetweenSegments(uint point, int* segmentA, int* segmentB);

uint __thiscall PathList::findSegmentIndex(int thisPtr, uint point)
{
    int count = *(int*)(thisPtr + 0xC);
    if (count == 0)
        return 0xFFFFFFFF;
    if (count == 1)
        return 0;

    uint currentIndex = *(uint*)(thisPtr + 0x4);
    int nextIndex;
    if (currentIndex < count - 1U)
        nextIndex = currentIndex + 1;
    else
        nextIndex = 0;

    int** segmentArray = *(int***)(thisPtr + 0x8);
    int* currentSegment = segmentArray[currentIndex];
    int* nextSegment = segmentArray[nextIndex];

    // Check if point is between current and next segment
    if (isPointBetweenSegments(point, currentSegment + 1, nextSegment + 1))
        return currentIndex;

    // Linear search through all segments
    uint i = 0;
    uint remaining = count;
    while (i < remaining)
    {
        if (i < count - 1)
            nextIndex = i + 1;
        else
            nextIndex = 0;

        int* segI = segmentArray[i];
        int* segNext = segmentArray[nextIndex];
        if (isPointBetweenSegments(point, segI + 1, segNext + 1))
            return i;

        remaining = *(uint*)(thisPtr + 0xC); // re-read count (unlikely to change)
        i++;
    }

    return 0xFFFFFFFF;
}