// FUNC_NAME: Array::pushBack
// Address: 0x008305b0
// Role: Push an element onto a dynamic array (vector-like container).
// The array structure has fields: data pointer at +0x00, size at +0x04, capacity at +0x08.
// If size == capacity, it grows (double or to 1 if empty) via a reallocation function.

void __thiscall Array::pushBack(uint32_t *this, uint32_t *element)
{
    uint32_t *dest;
    int newCapacity;

    if (this->size == this->capacity) {
        if (this->capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this->capacity * 2;
        }
        // Reallocate internal buffer to new capacity
        Array::reserve(newCapacity); // FUN_0082dc60
    }
    // Write element at end of array
    dest = this->data + this->size;
    this->size++;
    if (dest != nullptr) {
        *dest = *element;
    }
    return;
}