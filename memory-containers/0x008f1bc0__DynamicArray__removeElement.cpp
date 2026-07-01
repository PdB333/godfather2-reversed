// FUNC_NAME: DynamicArray::removeElement
void __thiscall DynamicArray::removeElement(int value) {
    uint count = this->size;          // +0x08
    uint index = 0;
    if (count == 0) return;
    int* array = this->data;          // +0x04
    while (array[index] != value) {
        index++;
        if (index >= count) {
            return;
        }
    }
    // Found element at index
    if (index != count - 1) {
        // Not the last element: move last element into the hole
        array[index] = array[count - 1];
    }
    this->size = count - 1;
}