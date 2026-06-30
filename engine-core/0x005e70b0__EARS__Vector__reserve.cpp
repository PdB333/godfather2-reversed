// FUNC_NAME: EARS::Vector::reserve
// Function address: 0x005e70b0
// Role: Increases capacity of a vector-like container (elements are 8 bytes each).
// Assumes contiguous layout: [data ptr, size, capacity] at offsets 0, 4, 8.

void EARS::Vector::reserve(uint newCapacity) {
    // Only increase capacity if requested is larger than current
    if (this->capacity < newCapacity) {
        // Allocate new block for newCapacity elements of 8 bytes each
        int* newData = (int*)malloc(newCapacity * 8);

        // Copy existing elements if any
        if (this->data != nullptr) {
            uint i = 0;
            int* src = this->data;
            int* dst = newData;
            while (i < this->size) {
                // Copy one 8-byte element
                dst[0] = src[0];
                dst[1] = src[1];
                i++;
                src += 2;
                dst += 2;
            }
            // Free old memory
            free(this->data);
        }

        // Update pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}