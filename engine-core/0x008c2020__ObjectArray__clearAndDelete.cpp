// FUNC_NAME: ObjectArray::clearAndDelete
// Address: 0x008c2020
// Role: Destructor/cleanup for a container that holds a dynamic array of elements (each 0x1c bytes) with a pointer at offset 0x10.
// Iterates from last element to first, deallocating each element's pointer (if non-null), then deallocates the array itself.

void ObjectArray::clearAndDelete() {
    int count = this->count - 1;            // param_1[1] - 1, number of elements minus one
    if (count >= 0) {
        int offset = count * 0x1c;          // byte offset to last element start
        do {
            // Element struct layout (size 0x1c):
            // +0x10: pointer to allocated object
            int* elementPtr = *(int**)(offset + 0x10 + this->array);  // param_1[0] is array base
            if (elementPtr != nullptr) {
                deallocate(elementPtr);     // FUN_009c8f10 - likely a delete/free
            }
            count--;
            offset -= 0x1c;                 // move to previous element
        } while (count >= 0);
    }
    if (this->array != nullptr) {
        deallocate(this->array);            // delete the array itself
    }
}