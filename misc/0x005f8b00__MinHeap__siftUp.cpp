// FUNC_NAME: MinHeap::siftUp
// Address: 0x005f8b00
// Role: Percolate an element up the min-heap to restore heap property after insertion.
// The heap data is stored as an array of 8-byte elements (int id at offset 0, float key at offset 4).
// this + 0x08 points to the heap array.
void __fastcall MinHeap::siftUp(int index)
{
    while (index > 1)
    {
        int parentIndex = index / 2;
        int* heapArray = *(int**)(this + 8);
        float parentKey = *(float*)(heapArray + 4 + parentIndex * 8);
        float currentKey = *(float*)(heapArray + 4 + index * 8);
        if (parentKey <= currentKey)
            return;

        // Swap the 8-byte elements at index and parentIndex
        int tempId = *(int*)(heapArray + index * 8);
        float tempKey = *(float*)(heapArray + 4 + index * 8);
        *(int*)(heapArray + index * 8) = *(int*)(heapArray + parentIndex * 8);
        *(float*)(heapArray + 4 + index * 8) = *(float*)(heapArray + 4 + parentIndex * 8);
        *(int*)(heapArray + parentIndex * 8) = tempId;
        *(float*)(heapArray + 4 + parentIndex * 8) = tempKey;

        index = parentIndex;
    }
}