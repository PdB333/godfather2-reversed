// FUNC_NAME: DynamicArray::addElement
// Reconstructed from 0x0054e310 - Adds an element (4 bytes) to a dynamic array.
// The calling class holds a pointer at this+0x14 to a buffer management struct.
// The buffer struct has:
//   +0x70: pointer to data array (int*)
//   +0x74: current element count (int)
//   +0x78: capacity with flags in high bits (int), real capacity = capacity & 0x3fffffff

class DynamicArray {
public:
    // Internal buffer management structure
    struct ArrayBuffer {
        int* data;        // +0x70
        int count;        // +0x74
        int capacityFlags; // +0x78
    };

    // This is called to expand the buffer when full.
    // (Replaces FUN_00aa4190 – likely a realloc-like function)
    void expandBuffer(int** dataPtr, int elementSize);

    void addElement(int value) {
        ArrayBuffer* buffer = *(ArrayBuffer**)(this + 0x14);
        int count = buffer->count;
        int realCapacity = buffer->capacityFlags & 0x3fffffff;

        if (count == realCapacity) {
            // Expand buffer (element size = 4 bytes)
            expandBuffer(&buffer->data, 4);
        }

        buffer->data[count] = value;
        buffer->count = count + 1;
    }
};