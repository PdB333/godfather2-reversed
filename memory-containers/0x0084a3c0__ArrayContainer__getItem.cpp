// FUNC_NAME: ArrayContainer::getItem
// Address: 0x0084a3c0
// Role: Returns pointer to element at given index, or null if out of bounds.
// Object layout:
//   +0x00: vtable pointer (implied by __thiscall)
//   +0x04: pointer to array of pointers (void**)
//   +0x08: number of elements (uint32_t)

void* __thiscall ArrayContainer::getItem(uint32_t index) {
    void* result = nullptr;
    if (index < this->count) { // count at +0x08
        result = this->array[index]; // array at +0x04, each element is 4 bytes
    }
    return result;
}