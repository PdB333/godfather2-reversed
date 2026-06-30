// FUNC_NAME: MinHeap::push

void __thiscall MinHeap::push(const HeapElement &elem)
// Function at 0x005fcce0: insert element into min-heap, maintaining heap property
// Class layout:
//   +0x00 HeapElement* data
//   +0x04 int size
//   +0x08 int capacity
{
    // Check if resize is needed
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        // FUN_005fc8f0 is reserve(newCapacity)
        reserve(newCapacity);
    }

    // Place element at the end and increment size
    HeapElement *slot = &data[size];
    slot->key = elem.key;
    slot->value = elem.value; // assuming 8-byte value; copies two 8-byte chunks
    ++size;

    // Sift-up to restore heap property
    int childIdx = size - 1;
    int parentIdx = (childIdx - 1) / 2;
    while (parentIdx >= 0) {
        if (data[parentIdx].key <= data[childIdx].key) {
            break;
        }
        // Swap the 16-byte elements
        HeapElement temp = data[childIdx];
        data[childIdx] = data[parentIdx];
        data[parentIdx] = temp;

        childIdx = parentIdx;
        parentIdx = (childIdx - 1) / 2;
    }
}