//FUNC_NAME: BinaryHeap::siftDown
// Function address: 0x005f8b50
// Role: Min-heap sift-down (percolate down) operation.
// The heap stores 8-byte elements: first 4 bytes (data), next 4 bytes (float key).
// Class layout: offset 0: size (int), offset 4: capacity (int, unused here), offset 8: pointer to heap array.

struct HeapElement {
    int data;   // +0x00
    float key;  // +0x04
};

class BinaryHeap {
public:
    int m_size;       // +0x00
    int m_capacity;   // +0x04 (unused in this function)
    HeapElement* m_data; // +0x08

    // __thiscall: this pointer in ECX, but the decompiler shows ESI used.
    // We'll assume the function is a member and use __thiscall.
    void __thiscall siftDown(int index);
};

void __thiscall BinaryHeap::siftDown(int index) {
    int size = this->m_size;
    int child;

    // While the parent has at least a left child
    while (index * 2 <= size) {
        child = index * 2; // left child index

        // If left child exists and right child is smaller (and not equal), choose right child
        if (child < size) {
            float leftKey = this->m_data[child].key; // left child's key
            float rightKey = this->m_data[child + 1].key; // right child's key
            if (rightKey <= leftKey && leftKey != rightKey) {
                child++; // choose right child
            }
        }

        // Compare parent key with chosen child key
        float parentKey = this->m_data[index].key;
        float childKey = this->m_data[child].key;
        if (parentKey < childKey || parentKey == childKey) {
            // Heap property satisfied
            return;
        }

        // Swap parent and child (8-byte elements)
        HeapElement temp = this->m_data[index];
        this->m_data[index] = this->m_data[child];
        this->m_data[child] = temp;

        // Move down to the child
        index = child;
        size = this->m_size;
    }
}