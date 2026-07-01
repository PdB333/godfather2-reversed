// FUNC_NAME: Array::insert
// Function address: 0x00949b10
// Inserts an element at the given index, shifting existing elements to the right.
// Returns a pointer to the newly inserted slot (8 bytes).
// The array stores elements of size 8 bytes (two 4-byte values).
// Object layout: [0] data pointer, [4] size (number of elements), [8] capacity (allocated slots)

class Array {
public:
    int* data;      // +0x00
    int size;       // +0x04
    int capacity;   // +0x08

    // Resize the array to newCapacity (calls FUN_00949490)
    void resize(int newCapacity);

    // Insert an element at index idx, shifting elements right.
    // Returns pointer to the inserted slot.
    int* insert(int idx) {
        if (size == capacity) {
            int newCap = (capacity == 0) ? 1 : capacity * 2;
            resize(newCap);
        }

        int* slot = data + idx * 2;  // each element is 8 bytes (2 ints)

        if (idx == size) {
            // Inserting at end: just increment size and return slot
            size++;
            return slot;
        }

        // Shift elements from idx to size-1 one position to the right
        // Copy element at position i-1 to position i
        for (int i = size; i > idx; i--) {
            int* dst = data + i * 2;
            int* src = data + (i - 1) * 2;
            dst[0] = src[0];
            dst[1] = src[1];
        }

        size++;
        return slot;
    }
};