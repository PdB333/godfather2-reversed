// FUNC_NAME: DynamicArray::reserve
// Function at 0x0054aee0 - Reserves capacity for a dynamic array.
// Structure offsets:
// +0x00: int* data (pointer to array elements)
// +0x04: int count (number of elements currently stored)
// +0x08: int capacity (allocated capacity in elements)
void DynamicArray::reserve(uint newCapacity) {
    // Only grow if new capacity is larger
    if (this->capacity < newCapacity) {
        // Allocate new buffer (each element is 4 bytes)
        int* newData = (int*)malloc(newCapacity * 4); // FUN_009c8e80

        if (this->data != 0) {
            // Copy existing elements into new buffer
            for (uint i = 0; i < this->count; i++) {
                if (newData != 0) {
                    newData[i] = this->data[i];
                }
            }
            // Free old buffer
            free(this->data); // FUN_009c8f10
        }
        // Update pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}