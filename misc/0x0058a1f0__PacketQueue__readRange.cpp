// FUNC_NAME: PacketQueue::readRange
// Address: 0x0058a1f0
// Copies a range of 12-byte elements from internal queue to output buffer.
// Advances queue internal pointer to targetIndex, then copies up to totalCount elements.
void __thiscall PacketQueue::readRange(int targetIndex, int* outputArray, QueueState* queue)
{
    int currentIndex = queue->count; // +0x4c

    // Fast-forward to targetIndex
    while (currentIndex < targetIndex)
    {
        queue->currentPtr += 3; // advance by 3 ints (12 bytes)
        queue->count = ++currentIndex;
    }

    int* srcPtr = (int*)queue->currentPtr; // +0x48
    int totalCount = this->totalElements; // unaff_ESI, overall element count

    // Copy until we reach totalCount
    while (currentIndex < totalCount)
    {
        outputArray[0] = srcPtr[0];
        outputArray[1] = srcPtr[1];
        outputArray[2] = srcPtr[2];
        srcPtr += 3;
        queue->currentPtr = srcPtr;
        queue->count = ++currentIndex;
        outputArray += 3;
    }
}