// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity)
{
    // If current capacity (offset +8) is less than requested newCapacity
    if (this->capacity < newCapacity) {
        // Allocate new block of newCapacity * sizeof(int) bytes
        int* newData = (int*)malloc(newCapacity * sizeof(int));
        
        // If there is existing data, copy elements up to current size (offset +4)
        if (this->data != nullptr && this->size > 0) {
            for (uint i = 0; i < this->size; i++) {
                newData[i] = this->data[i];
            }
        }
        
        // Free old data if any
        if (this->data != nullptr) {
            free(this->data);
        }
        
        // Update data pointer and capacity (size unchanged)
        this->data = newData;
        this->capacity = newCapacity;
    }
}