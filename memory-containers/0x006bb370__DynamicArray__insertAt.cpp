// FUNC_NAME: DynamicArray::insertAt
// 0x006bb370 - Inserts a new element slot at the given index, shifting subsequent elements right. Returns pointer to the slot (caller must write the element).
// Container: pointer array with fields: +0x00 data pointer, +0x04 size, +0x08 capacity.

class DynamicArray {
public:
    int*   data;     // +0x00
    int    size;     // +0x04
    int    capacity; // +0x08

    // Grow capacity (defined elsewhere)
    void grow(int newCapacity);

    // Insert at index, returns pointer to the reserved slot
    int* insertAt(uint index) {
        // Ensure capacity
        if (size == capacity) {
            int newCap = (capacity == 0) ? 1 : capacity * 2;
            grow(newCap); // may reallocate data, update capacity
        }

        int* arr = data;        // re-read after potential reallocation
        int curSize = size;

        // Append at end?
        if (index == (uint)curSize) {
            size = curSize + 1;
            return &arr[curSize];
        }

        // Shift elements to make room at 'index'
        // Duplicate last element to the new end slot (capacity is sufficient)
        int* endSlot = &arr[curSize];
        *endSlot = *(endSlot - 1);   // copy last element to end

        // Shift block [index, curSize-2] one position right
        for (int i = curSize - 1; i > (int)index; i--) {
            arr[i] = arr[i - 1];
        }

        size = curSize + 1;
        return &arr[index];
    }
};