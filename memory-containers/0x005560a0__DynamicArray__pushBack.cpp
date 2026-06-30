// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, const int *value) {
    // Check if the array is full (index == (capacity & 0x3FFFFFFF))
    if (this[1] == (this[2] & 0x3FFFFFFF)) {
        // Resize the array; second parameter is element size (4 bytes)
        FUN_00aa4190(this, 4);
    }
    // Write the value to the current position
    *(int *)(this[0] + this[1] * 4) = *value;
    // Increment count
    this[1] = this[1] + 1;
}