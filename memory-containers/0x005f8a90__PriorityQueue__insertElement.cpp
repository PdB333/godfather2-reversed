// FUNC_NAME: PriorityQueue::insertElement
// Function address: 0x005f8a90
// This function inserts an element with a float key into a binary min-heap.
// The heap is stored as a dynamic array of 8-byte entries (structure: int id, float key).
// The heap structure (at 'this') contains:
// +0x00: current size (int)
// +0x04: capacity (int)
// +0x08: pointer to heap array (int*)
// The element structure (at 'elementId') has a byte at offset 0x0A that is marked as "inHeap".

uint __thiscall PriorityQueue::insertElement(int elementId, float key)
{
    int currentSize;
    int parentIndex;
    int newIndex;
    int *heapArray;
    uint returnVal;

    // Use EAX value passed in as base for return (likely a handle or status)
    returnVal = this->handleBase & 0xffffff00;

    // Check if there is room (size < capacity - 1)
    if (this->size < this->capacity - 1) {
        newIndex = this->size + 1;
        this->size = newIndex;

        // Sift up: find the correct insertion point
        while (newIndex > 1) {
            parentIndex = newIndex / 2;
            heapArray = this->heapArray;
            // Compare key with parent's key at offset +4 of each 8-byte entry
            if (*(float *)((int)heapArray + 4 + parentIndex * 8) <= key) {
                break;
            }
            // Move parent down to current position
            *(int *)((int)heapArray + newIndex * 8) = *(int *)((int)heapArray + parentIndex * 8);
            *(float *)((int)heapArray + 4 + newIndex * 8) = *(float *)((int)heapArray + 4 + parentIndex * 8);
            newIndex = parentIndex;
        }

        // Insert the new element
        heapArray = this->heapArray;
        *(int *)((int)heapArray + newIndex * 8) = elementId;
        *(float *)((int)heapArray + 4 + newIndex * 8) = key;

        // Mark the element as present in the heap (bit 0 at offset 0x0A)
        *(byte *)(elementId + 0x0A) |= 1;

        // Build return value: high 24 bits of heap array pointer, low byte = 1
        returnVal = ((uint)heapArray >> 8) & 0x00FFFFFF; // Actually CONCAT31(a,1) = (a >> 8) << 8 | 1
        // The original Ghidra shows CONCAT31((int3)((uint)iVar1 >> 8),1) which is (iVar1 >> 8) << 8 | 1
        // Since iVar1 is heapArray, this becomes (heapArray & 0xFFFFFF00) | 1
        returnVal = ((uint)heapArray & 0xFFFFFF00) | 1;
    }

    return returnVal;
}